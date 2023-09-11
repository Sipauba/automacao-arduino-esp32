const int buttonPin = 2; // Pino do botão (conectado ao pino 2 do ESP32)

void setup() {
  pinMode(buttonPin, INPUT_PULLUP); // Configura o pino do botão como entrada com pull-up interno
  Serial.begin(115200); // Inicializa a comunicação serial
}

void loop() {
  // Verifica se o botão foi pressionado (estado LOW devido ao pull-up)
  if (digitalRead(buttonPin) == HIGH) {
    Serial.println("Botão foi pressionado!");
    delay(100); // Aguarde um segundo para evitar detecções repetidas
  }
}
