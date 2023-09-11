// Define o pino do LED embutido no ESP32 DevKit V1
#define LED_BUILTIN 2

void setup() {
  pinMode(LED_BUILTIN, OUTPUT); // Configura o pino LED_BUILTIN como saída
}

void loop() {
  digitalWrite(LED_BUILTIN, HIGH); // Liga o LED_BUILTIN
  delay(1000); // Espera por 1 segundo
  digitalWrite(LED_BUILTIN, LOW); // Desliga o LED_BUILTIN
  delay(1000); // Espera por 1 segundo
}
