#include <Thermistor.h>
#include <SevSeg.h>
//OBS: A biblioteca Thermistor está configurada pra ser usada apenas no arduino UNO, já que a voltagem padrão é de 5.0 V
Thermistor thermistor(0); // Conecte o termistor ao pino analógico A0
SevSeg sevseg;

void setup() {
  Serial.begin(9600);
  byte numDigits = 2; //A quantidade de dígitos
  byte digitPins[] = {2, 3}; //Os pinos digitais que irão enviar o sinal VCC para cada Display (liga/desliga)
  byte segmentPins[] = {4, 5, 6, 7, 8, 9, 10, 11}; //Os pinos digitais que irão enviar o sinal para cada segmento dos displays
  //OSB: Nesse caso são dois displays, esses pinos controlarão ambos os displays (1 pino digital para dais seguimentos)
  //O que faz exibir os dois números corretamente são os 2 pinos digitais que ligam e desligam, alternando os números que serão exibidos
  //Ficam piscando tão rápido que não dá pra notar 
  //4 = A
  //5 = B
  //6 = C
  //7 = D
  //8 = E
  //9 = F
  //10 = G
  //11 = PONTO
  sevseg.begin(COMMON_CATHODE, numDigits, digitPins, segmentPins);
}

void loop() {

  float temperature = thermistor.getTemp();
  int temperatureRounded = (int) temperature;
  sevseg.setNumber(temperatureRounded, 2); //O número 2 define quantas casas decimais 
  sevseg.refreshDisplay();
  Serial.println(temperature);

}
