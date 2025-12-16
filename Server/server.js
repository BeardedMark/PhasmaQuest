import { WebSocketServer } from "ws";

const wss = new WebSocketServer({ port: 8080 });
const devices = new Map(); // deviceId -> ws

wss.on("connection", (ws) => {
  console.log("🟢 Новое подключение устройства");

  let deviceId = null;

  ws.on("message", (msg) => {
    const data = msg.toString();
    console.log(`Получено сообщение: ${data}`);
    const arr = data.split("/");

    switch (arr[1]) {
      case "register":
        deviceId = arr[2];
        devices.set(deviceId, ws);
        console.log(`Устройство зарегистрировалось: ${deviceId}`);
        ws.send(`Успешная регистрация на сервере: ${deviceId}`);
        break;

      case "send":
        const targetId = arr[2];         // новое имя переменной
        const targetWS = devices.get(targetId);
        if (targetWS) {
          targetWS.send(arr[3]);
        }
        break;

      default:
        break;
    }
  });

  ws.on("close", () => {
    if (deviceId) {
      devices.delete(deviceId);
      console.log(`🟡 Устройство отключилось: ${deviceId}`);
    }
  });
});

function sendTo(deviceId, data) {
  const targetWS = devices.get(deviceId);
  if (targetWS) {
    targetWS.send(JSON.stringify(data));
    console.log(`Отправлено ${deviceId}:`, data);
  }
}
