#include <WebServer.h>
#include <WiFiManager.h>

WiFiManager wifiManager;
WebServer server(80);

int valor = 0;

void handleRoot() {
  String content = "<html><body><h1>Valor:</h1><p><input type='text' id='valor' value='" + String(valor) + "' readonly='readonly'></p></body></html>";
  content += "<script>setInterval(function() { fetch('/atualiza-valor').then(response => response.text()).then(valor => document.getElementById('valor').value = valor); }, 500);</script>";
  server.send(200, "text/html", content);
}

void handleAtualizaValor() {
  server.send(200, "text/plain", String(valor));
}

void setup() {
  // Inicia o WiFi Manager
  wifiManager.autoConnect();

  // Configura a rota para a página web
  server.on("/", handleRoot);

  server.on("/atualiza-valor", handleAtualizaValor);

  // Inicia o servidor web
  server.begin();

}

void loop(){
  server.handleClient();
  valor++;
  delay(500);
}
