const int analogInPin = 34; // Pino de entrada analógico
float R1 = 10000; // Resistor do termoresistor
float logR2, R2, T; //Apenas declarando o tipo primitivo das variáveis que serão utilizadas
float c1 = 0.001129148, c2 = 0.000234125, c3 = 0.0000000876741; // Coeficientes Steinhart-Hart
//Equação de Steinhart-Hart 1/T = c1 + c2 ln(R) + c3 ln(R)^3
//Esses valores dos coeficientes são específicos para cada termistor, verificar a documentação
void setup() {
  Serial.begin(9600);
}

void loop() {
  int rawValue = analogRead(analogInPin); //O valor limpo e seco recebido lido da porta analógica
  float voltage = rawValue * (3.3 / 4096.0); // Conversão da leitura analógica para tensão
  //Equação para o cálculo da tensão TENSÃO = (VALOR_ANALÓGICO * TENSÃO DE ALIMENTAÇÃO DO SISTEMA)/VALOR MÁXIMO DA LEITURA ANALÓGICA DO MICRO CONTROLADOR
  //NO caso do esp32, o valor máximo da leitura analógica é 4096
  R2 = R1 * (3.3 / voltage - 1); // Cálculo da resistência do termoresistor
  logR2 = log(R2);
  T = (1.0 / (c1 + c2*logR2 + c3*logR2*logR2*logR2)); // Cálculo da temperatura em graus Celsius
  T = T - 273.15; // Conversão para Celsius
  Serial.print("Temperatura: ");
  Serial.print(T);
  Serial.println("C");
  delay(500);
}

//Lembrando que precisa estar conectado um resistor PULL UP de 10K (por conta do termistor que é de 10K também)
//o PULL UP fica uma ponta do resistor ligado no GND (-) e a outra ponta ligada junto com o termistor
//Conecte um resistor de 10K ohms entre o pino de entrada analógica do ESP32 e a fonte de tensão do ESP32 (+)

//NA DUVIDA INVERTE OS PINOS GND E VCC
