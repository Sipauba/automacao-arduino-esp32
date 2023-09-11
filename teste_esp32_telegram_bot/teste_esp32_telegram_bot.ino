#include <WiFi.h>
#include <HTTPClient.h>

const char* ssid = "NERO";           // Nome da sua rede Wi-Fi
const char* password = "85690139";   // Senha da sua rede Wi-Fi
const char* botToken = "6504531209:AAEETGnQg4puFVo8awN3IJXXm81DPZWx3Pw";  // Token do seu bot do Telegram
const int groupChatId = -4038144360;   // Substitua pelo ID do chat do seu grupo

void setup() {
  Serial.begin(115200);

  // Conectar ao Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Conectando ao WiFi...");
  }
  Serial.println("Conectado ao Wi-Fi");

  // Enviar uma mensagem simples "OI" para o grupo do Telegram
  sendTelegramMessage("OI");
}

void loop() {
  // Coloque seu código principal aqui, se necessário
}

void sendTelegramMessage(const String& message) {
  HTTPClient http;

  String url = "https://api.telegram.org/bot" + String(botToken) + "/sendMessage";
  String payload = "chat_id=" + String(groupChatId) + "&text=" + message;

  http.begin(url);
  http.addHeader("Content-Type", "application/x-www-form-urlencoded");

  int httpCode = http.POST(payload);

  if (httpCode > 0) {
    String response = http.getString();
    Serial.println("Mensagem enviada com sucesso!");
    Serial.println(response);
  } else {
    Serial.println("Falha ao enviar a mensagem.");
  }

  http.end();
}
