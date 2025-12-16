#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEScan.h>

BLEScan* scan;
const int emf1 = 18;
const int emf2 = 19;
const int emf3 = 21;
const int emf4 = 22;
const int emf5 = 23;
const int buzzer = 5;
const int defled = 2;

float calculateDistance(int rssi, int txPower = -59) {
  float n = 2.0;
  return pow(10, ((txPower - rssi) / (10 * n)));
}

class MyCallbacks : public BLEAdvertisedDeviceCallbacks {
  void onResult(BLEAdvertisedDevice device) {
    if (device.getName() == "GHOST") {
      int rssi = device.getRSSI();
      float dist = calculateDistance(rssi);
      String message = device.getManufacturerData().c_str();

      digitalWrite(defled, HIGH);

      if (dist < 5) {
        setEmf(message);
      }
      digitalWrite(defled, LOW);
    }
  }
};

void setup() {
  pinMode(emf1, OUTPUT);
  pinMode(emf2, OUTPUT);
  pinMode(emf3, OUTPUT);
  pinMode(emf4, OUTPUT);
  pinMode(emf5, OUTPUT);
  pinMode(defled, OUTPUT);

  pinMode(buzzer, OUTPUT);
  digitalWrite(buzzer, HIGH);

  BLEDevice::init("");
  scan = BLEDevice::getScan();
  scan->setActiveScan(true);
  scan->setAdvertisedDeviceCallbacks(new MyCallbacks(), true);
  scan->start(0, nullptr, false);
}

void loop() {
  // if (emf == "1") {
  //   tone(buzzer, 10);
  //   digitalWrite(emf1, HIGH);
  //   digitalWrite(emf2, LOW);
  //   digitalWrite(emf3, LOW);
  //   digitalWrite(emf4, LOW);
  //   digitalWrite(emf5, LOW);
  // } else if (emf == "2") {
  //   tone(buzzer, 20);
  //   digitalWrite(emf1, HIGH);
  //   digitalWrite(emf2, HIGH);
  //   digitalWrite(emf3, LOW);
  //   digitalWrite(emf4, LOW);
  //   digitalWrite(emf5, LOW);
  // } else if (emf == "3") {
  //   tone(buzzer, 30);
  //   digitalWrite(emf1, HIGH);
  //   digitalWrite(emf2, HIGH);
  //   digitalWrite(emf3, HIGH);
  //   digitalWrite(emf4, LOW);
  //   digitalWrite(emf5, LOW);
  // } else if (emf == "4") {
  //   tone(buzzer, 40);
  //   digitalWrite(emf1, HIGH);
  //   digitalWrite(emf2, HIGH);
  //   digitalWrite(emf3, HIGH);
  //   digitalWrite(emf4, HIGH);
  //   digitalWrite(emf5, LOW);
  // } else if (emf == "5") {
  //   tone(buzzer, 50);
  //   digitalWrite(emf1, HIGH);
  //   digitalWrite(emf2, HIGH);
  //   digitalWrite(emf3, HIGH);
  //   digitalWrite(emf4, HIGH);
  //   digitalWrite(emf5, HIGH);
  // } else {
  //   noTone(buzzer);
  //   digitalWrite(emf5, LOW);
  //   digitalWrite(emf4, LOW);
  //   digitalWrite(emf3, LOW);
  //   digitalWrite(emf2, LOW);
  //   digitalWrite(emf1, LOW);
  // }
}

void setEmf(String emf) {
  if (emf == "1") {
    tone(buzzer, 10);
    digitalWrite(emf1, HIGH);
    digitalWrite(emf2, LOW);
    digitalWrite(emf3, LOW);
    digitalWrite(emf4, LOW);
    digitalWrite(emf5, LOW);
  } else if (emf == "2") {
    tone(buzzer, 20);
    digitalWrite(emf1, HIGH);
    digitalWrite(emf2, HIGH);
    digitalWrite(emf3, LOW);
    digitalWrite(emf4, LOW);
    digitalWrite(emf5, LOW);
  } else if (emf == "3") {
    tone(buzzer, 30);
    digitalWrite(emf1, HIGH);
    digitalWrite(emf2, HIGH);
    digitalWrite(emf3, HIGH);
    digitalWrite(emf4, LOW);
    digitalWrite(emf5, LOW);
  } else if (emf == "4") {
    tone(buzzer, 40);
    digitalWrite(emf1, HIGH);
    digitalWrite(emf2, HIGH);
    digitalWrite(emf3, HIGH);
    digitalWrite(emf4, HIGH);
    digitalWrite(emf5, LOW);
  } else if (emf == "5") {
    tone(buzzer, 50);
    digitalWrite(emf1, HIGH);
    digitalWrite(emf2, HIGH);
    digitalWrite(emf3, HIGH);
    digitalWrite(emf4, HIGH);
    digitalWrite(emf5, HIGH);
  } else {
    noTone(buzzer);
    digitalWrite(emf5, LOW);
    digitalWrite(emf4, LOW);
    digitalWrite(emf3, LOW);
    digitalWrite(emf2, LOW);
    digitalWrite(emf1, LOW);
  }
}
