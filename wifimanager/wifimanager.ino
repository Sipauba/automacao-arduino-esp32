#include <WiFiManager.h>

// Defina o nome da rede de configuração
char wifiManagerSSID[] = "ESP32-Config";

const int botaoReset = 2; // Por exemplo, use o pino 2 para conectar o botão

void setup() {
  Serial.begin(115200);

  // Inicializa o WiFiManager
  WiFiManager wifiManager;

  // Inicia a configuração WiFi com o nome da rede de configuração
  if (!wifiManager.autoConnect(wifiManagerSSID)) {
    Serial.println("Falha na Conexão WiFi");
    delay(1000);
    // Reinicie o dispositivo ou faça alguma outra ação aqui
  }

  // Se chegou aqui, a conexão WiFi foi estabelecida
  Serial.println("Conectado à rede WiFi!");

}

void loop() {
  // Seu código principal aqui
}
