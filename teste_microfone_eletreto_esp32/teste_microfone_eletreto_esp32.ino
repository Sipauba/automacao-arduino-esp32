const int microphonePin = 34;  // Pino analógico usado para ler o sinal do microfone

void setup() {
  Serial.begin(9600);  // Inicializa a comunicação serial
}

void loop() {
  // Lê o valor analógico do microfone
  int microphoneValue = analogRead(microphonePin);

  // Imprime o valor lido no monitor serial
  Serial.println(microphoneValue);

  // Aguarda um curto intervalo antes de ler novamente
  delay(100);  // Você pode ajustar o valor do atraso conforme necessário
}
