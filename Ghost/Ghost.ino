#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEAdvertising.h>

const String name = "GHOST";
const int defBtnPin = 4;
const int defLedPin = 2;
int emfPower = 5;

BLEAdvertising *advertising;

void setup() {
  pinMode(defBtnPin, INPUT_PULLUP);
  pinMode(defLedPin, OUTPUT);

  BLEDevice::init("ESP32_BEACON");
  advertising = BLEDevice::getAdvertising();
}

void loop() {
  if (digitalRead(defBtnPin) == LOW) {
    digitalWrite(defLedPin, HIGH);
    int randValue = random(1, emfPower + 1);
    setSignal(name, String(randValue));
    delay(1000);
    advertising->stop();
  } else {
    digitalWrite(defLedPin, LOW);
  }
}

void setSignal(String name, String data) {
  // digitalWrite(defLedPin, HIGH);

  BLEAdvertisementData advData;
  advData.setName(name);
  advData.setManufacturerData(String(data));
  advertising->setAdvertisementData(advData);
  advertising->start();

  // digitalWrite(defLedPin, LOW);
}