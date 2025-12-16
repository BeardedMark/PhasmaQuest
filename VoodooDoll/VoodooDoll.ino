#include <WiFi.h>
#include <WebSocketsClient.h>

WebSocketsClient ws;

void onWebSocketEvent(WStype_t type, uint8_t* payload, size_t length) {
  switch (type) {
    case WStype_CONNECTED:
      ws.sendTXT("/register/VoodooDoll");
      break;
    case WStype_TEXT:
      break;
    case WStype_DISCONNECTED:
      break;
  }
}

void setup() {
  pinMode(0, INPUT_PULLUP);

  WiFi.begin("M3G", "20101995");
  while (WiFi.status() != WL_CONNECTED) { delay(1000); }

  ws.begin("192.168.0.30", 8080, "/");
  ws.onEvent(onWebSocketEvent);
  ws.setReconnectInterval(2000);
}

void loop() {
  ws.loop();

  static bool last = HIGH;
  bool now = digitalRead(0);

  if (last != now && now == LOW) {
    ws.sendTXT("/activate/VoodooDoll");
  }

  last = now;
}
