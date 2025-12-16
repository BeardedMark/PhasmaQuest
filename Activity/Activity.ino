#include <WiFi.h>
#include <WebSocketsClient.h>
#include <NimBLEDevice.h>
#include <ESP32Servo.h>

WebSocketsClient ws;
NimBLEAdvertising* advertising;
Servo servo;

const int light = 2;

void on() {
  int value = random(1, 5);
  String msg = String(value); 
  setBleSignal("EPF", msg.c_str()); 
  advertising->start();

  servo.write(30);
  digitalWrite(light, HIGH);
}

void off() {
  advertising->stop();
  servo.write(0);
  digitalWrite(light, LOW);
}

void play(int time = 300) {
  on();
  delay(time);
  off();
}

void epf(String level) {
  String s = level;
  const char* c = s.c_str();
  
  setBleSignal("EPF", c); 
  advertising->start();
  delay(3000);
  off();
}

void handleIncomingMessage(const char* message) {
  String msg = String(message);
  msg.trim();

  int first = msg.indexOf(':');
  String cmd = first == -1 ? msg : msg.substring(0, first);
  String arg = first == -1 ? "" : msg.substring(first + 1);

  if (cmd == "on") { on(); }
  if (cmd == "off") { off(); }
  if (cmd == "play") { play(); }
  if (cmd == "epf") { epf(arg); }
}

void onWebSocketEvent(WStype_t type, uint8_t* payload, size_t length) {
  switch (type) {
    case WStype_CONNECTED:
      ws.sendTXT("/register/picture");
      break;
    case WStype_TEXT:
      handleIncomingMessage((char*)payload);
      break;
    case WStype_DISCONNECTED:
      break;
  }
}

void setupWebSocket(const char* ip, const int port, const int interval = 2000) {
  ws.begin(ip, port, "/");
  ws.onEvent(onWebSocketEvent);
  ws.setReconnectInterval(interval);
}

void setupWiFi(const char* name, const char* pass, const int await = 1000) {
  WiFi.begin(name, pass);
  while (WiFi.status() != WL_CONNECTED) { delay(await); }
}

void setBleSignal(const char* name, const char* message) {
  NimBLEAdvertisementData advData;
  advData.setName(name);
  advData.setManufacturerData(message);
  advertising->setAdvertisementData(advData);
}

void setupBluetooth() {
  NimBLEDevice::init("ESP32_BEACON");
  advertising = NimBLEDevice::getAdvertising();
}

void setup() {
  pinMode(light, OUTPUT);
  randomSeed(analogRead(0));
  servo.attach(26);

  setupWiFi("M3G", "20101995");
  setupWebSocket("192.168.0.30", 8080);
  setupBluetooth();
}

void loop() {
  ws.loop();
}