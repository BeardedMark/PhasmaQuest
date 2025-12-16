#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEScan.h>

#include <Wire.h>
#include <LiquidCrystal_I2C.h>

bool isNegative = false;
int distance = 0;
int currentTemp = 0;

LiquidCrystal_I2C lcd(0x27, 16, 2);
BLEScan* scan;

float calculateDistance(int rssi, int txPower = -59) {
  float n = 2.0;
  return pow(10, ((txPower - rssi) / (10 * n)));
}

void printLine(int line, String text = "                ", int pos = 0) {
  lcd.setCursor(pos - 1, line - 1);
  lcd.print("                ");
  lcd.setCursor(pos - 1, line - 1);
  lcd.print(text);
}

void printTemperature() {
  int minTempNear = isNegative ? -3 : 0;   // температура рядом
  int maxTempNear = 5;

  int minTempFar = 5;
  int maxTempFar = 25;

  int minDist = 3;
  int maxDist = 10;

  // ограничиваем дистанцию в пределах
  int d = constrain(distance, minDist, maxDist);

  int minRand = map(d, minDist, maxDist, minTempNear, minTempFar);
  int maxRand = map(d, minDist, maxDist, maxTempNear, maxTempFar);

  // плавное изменение температуры
  int change = random(-1, 2);  // -1, 0 или +1
  currentTemp += change;

  // держим температуру в пределах
  currentTemp = constrain(currentTemp, minRand, maxRand);

  printLine(2, String(currentTemp) + " *C");
}

class MyCallbacks : public BLEAdvertisedDeviceCallbacks {
  void onResult(BLEAdvertisedDevice device) {

    if (device.getName() == "Temperature") {
      int rssi = device.getRSSI();
      float dist = calculateDistance(rssi);
      String message = device.getManufacturerData().c_str();

      isNegative = message == "1";
      distance = dist;
    }
  }
};

void setup() {
  Serial.begin(115200);
  delay(200);

  lcd.init();
  lcd.backlight();

  randomSeed(analogRead(0));

  BLEDevice::init("");
  scan = BLEDevice::getScan();
  scan->setActiveScan(true);
  scan->setAdvertisedDeviceCallbacks(new MyCallbacks(), true);
  scan->start(1000, nullptr, false);
}

void loop() {
  printLine(1, "Temperature: ");
  printTemperature();
  delay(500);
}
