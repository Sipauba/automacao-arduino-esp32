int portaAnalogica = 32; // define a porta ADC que será usada
float tensaoRef = 3.3; // define a tensão de referência do ADC em volts
float resistenciaRef = 10000; // define a resistência de referência do termistor em ohms
float beta = 3950; // define o coeficiente beta do termistor

void setup() {
  Serial.begin(9600);
}

void loop() {
  int valorADC = analogRead(portaAnalogica); // lê o valor da porta ADC
  float tensao = (valorADC / 4095.0) * tensaoRef; // calcula a tensão da porta ADC em volts
  float resistencia = resistenciaRef * ((tensaoRef / tensao) - 1); // calcula a resistência do termistor em ohms
  float temperatura = (1 / ((1 / 298.15) + (1 / beta) * log(resistencia / 10000))) - 273.15; // calcula a temperatura em graus Celsius
  Serial.println(temperatura); // imprime a temperatura na porta serial
  delay(1000); // espera um segundo antes de ler novamente
}
