#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEAdvertising.h>

const int btnPin = 0;
const int ledPin = 2;
bool isNegative = false;

BLEAdvertising *advertising;

void startBle() {
  BLEAdvertisementData advData;
  advData.setName("Presence");
  advData.setManufacturerData(String(isDanger));

  advertising->setAdvertisementData(advData);
  advertising->start();
}

void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(btnPin, INPUT_PULLUP);

  BLEDevice::init("ESP32_BEACON");
  advertising = BLEDevice::getAdvertising();
  startBle();
}

void loop() {
  if (digitalRead(btnPin) == LOW) {
    isNegative = !isNegative;
    startBle();
    delay(300);
  }

  if (isNegative) {
    digitalWrite(ledPin, HIGH);
  } else {
    digitalWrite(ledPin, LOW);
  }
}