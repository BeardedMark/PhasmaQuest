#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEScan.h>

#include <Wire.h>
#include <LiquidCrystal_I2C.h>

const int buzzer = 5;

LiquidCrystal_I2C lcd(0x27, 16, 2);
BLEScan* scan;

class MyCallbacks : public BLEAdvertisedDeviceCallbacks {
  void onResult(BLEAdvertisedDevice device) {

    if (device.getName() == "EPF") {
      int rssi = device.getRSSI();
      float dist = pow(10, ((-59 - rssi) / (10 * 2.0)));
      String message = device.getManufacturerData().c_str();

      lcd.setCursor(0, 0);
      lcd.print("                    ");
      lcd.setCursor(0, 0);
      lcd.print("EMF: ");
      lcd.print(message);
      lcd.print(" (");
      lcd.print(dist);
      lcd.print("m)");
    }
  }
};

void setupBleScaner() {
  BLEDevice::init("");
  scan = BLEDevice::getScan();
  scan->setActiveScan(true);
  scan->setAdvertisedDeviceCallbacks(new MyCallbacks(), true);
}

void setup() {
  lcd.init();
  lcd.backlight();

  pinMode(buzzer, OUTPUT);
  digitalWrite(buzzer, LOW);

  setupBleScaner();
  // scan->start(1000, nullptr, false);
}

void loop() {
  scan->start(200, false);
  delay(3000);
}
