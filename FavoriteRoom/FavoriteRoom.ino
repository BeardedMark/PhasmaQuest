#include <WiFi.h>
#include <WebSocketsClient.h>
#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEAdvertising.h>

WebSocketsClient ws;
BLEAdvertising *advertising;


void setBleSignal(String name, String message) {
  BLEAdvertisementData advData;
  advData.setName(name);
  advData.setManufacturerData(message);
  advertising->setAdvertisementData(advData);
}

void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(btnPin, INPUT_PULLUP);
  
  WiFi.begin("M3G", "20101995");
  while (WiFi.status() != WL_CONNECTED) { delay(1000); }

  ws.begin("192.168.0.30", 8080, "/");
  ws.onEvent(onWebSocketEvent);
  ws.setReconnectInterval(2000);

  BLEDevice::init("ESP32_BEACON");
  advertising = BLEDevice::getAdvertising();
  setBleSignal("FavoriteRoom", "MESSAGE");
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