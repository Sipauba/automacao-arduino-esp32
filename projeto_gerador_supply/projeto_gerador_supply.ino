
#include <WiFiManager.h>
#include <LiquidCrystal_I2C.h>
#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>
#include <ArduinoJson.h>

#define BOT_TOKEN "6504531209:AAEETGnQg4puFVo8awN3IJXXm81DPZWx3Pw"

#define CHAT_ID "-4038144360"

WiFiClientSecure secured_client;
UniversalTelegramBot bot(BOT_TOKEN, secured_client);
const unsigned long BOT_MTBS = 10000; // mean time between scan messages
unsigned long bot_lasttime; // last time messages' scan has been done


char wifiManagerSSID[] = "ESP32"; //define o nome da rede para se conectar na rede do ESP32

int lcdColunas = 16;
int lcdLinhas = 2;
LiquidCrystal_I2C lcd(0x27, lcdColunas, lcdLinhas);

const int botaoReset = 2; //porta D2 do ESP32

static bool monitorando_barulho = false;
static bool gerador_ligado = false;
static bool gerador_desligando = false;

//TERMISTOR
const int analogInPin = 34; // Pino de entrada analógico
float R1 = 10000; // Resistor do termoresistor
float logR2, R2, T; //Apenas declarando o tipo primitivo das variáveis que serão utilizadas
float c1 = 0.001129148, c2 = 0.000234125, c3 = 0.0000000876741; // Coeficientes Steinhart-Hart

const int microfone = 15; // Porta D15 (GPIO15) para leitura analógica

unsigned long tempo_contagem = 0; // Variável para controlar o tempo de contagem

void setup() {

  pinMode(microfone,INPUT);
  
  Serial.begin(115200);
  
  lcd.init(); //liga o display LCD
  lcd.backlight();
  
  lcd.setCursor(0,0);
  lcd.print("Conectando...");

  WiFiManager wifiManager; //inicia a conexão com o wifi

  pinMode(botaoReset, INPUT_PULLUP); //configura o botão do reset para ser acionado ao pressinar

  wifiManager.setConfigPortalTimeout(10); //configura o programa para tentar se conectar à rede já salva por 10 segundos
  // se passar os 10 segundos enão conectar, o ESP irá ligar o modo AP para configurar a nova rede wifi

  if (wifiManager.autoConnect(wifiManagerSSID)) { //caso se conecte à uma rede já salva anteriormente
    Serial.println("Conexão bem Sucedida");
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("CONECTADO!");
    delay(1000);
    lcd.clear();
  } 
  else { // caso não se conecte em 10 segundos, será solicitado que faça a configuração da nova rede 
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Rede: ESP32");
    lcd.setCursor(0,1);
    lcd.print("Nav. 192.168.4.1");
    wifiManager.setConfigPortalTimeout(false); //desliga o modo TimeOut para que não encerre
    wifiManager.autoConnect(); //Inicia o AP para se conectar à rede do ESP e configurar uma nova rede
    delay(1000);
  }

  secured_client.setCACert(TELEGRAM_CERTIFICATE_ROOT); // Add root certificate for api.telegram.org

}

void resetRede(){ //Essa função irá resetar a rede salva na memória ao pressionar o botão de reset do dispositivo, sendo necessário configurar novamente
  WiFiManager wifiManager;
  Serial.println("Resetando rede...");
  wifiManager.resetSettings();
}

void mensagem(const char* texto){
  secured_client.setCACert(TELEGRAM_CERTIFICATE_ROOT); 
  Serial.print("Retrieving time: ");
  configTime(0, 0, "pool.ntp.org"); // get UTC time via NTP
  time_t now = time(nullptr);
  while (now < 24 * 3600){
    Serial.print(".");
    delay(100);
    now = time(nullptr);
  }
  Serial.println(now);

  bot.sendMessage(CHAT_ID, texto, "");
}

void handleNewMessages(int numNewMessages){
  for (int i = 0; i < numNewMessages; i++) {
    String mensagemEnviada = bot.messages[i].text;

    if (mensagemEnviada.startsWith("@seubot") or mensagemEnviada.indexOf("/teste") != -1){
      mensagem("Testando \nQuebra \nde \nLinha");
    }
  }
}

void loop() {
  
  if (millis() - bot_lasttime > BOT_MTBS)
  {
    int numNewMessages = bot.getUpdates(bot.last_message_received + 1);

    while (numNewMessages)
    {
      Serial.println("got response");
      handleNewMessages(numNewMessages);
      numNewMessages = bot.getUpdates(bot.last_message_received + 1);
    }

    bot_lasttime = millis();
  }
  
  if (digitalRead(botaoReset) == HIGH){ //Código relacionado ao botão de RESET
    Serial.println("Resetando...");
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Resetando...");
    resetRede();
    //wifiManager.resetSettings();
    delay(1000);
    lcd.clear();
    ESP.restart();
  }

  //TERMISTOR
  
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
  delay(1000);

  int leitura = digitalRead(microfone);

  if (leitura == LOW and monitorando_barulho == false and gerador_ligado == false){
    Serial.println("Gerador DESLIGADO");;
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Ger.: DESLIGADO");
  }

  if (leitura == HIGH and monitorando_barulho == false){
    Serial.println("Contagem para ligar...");
    monitorando_barulho = true;
    tempo_contagem = millis();
    mensagem("Contagem para ligar...");
  }

  if (monitorando_barulho == true and (millis() - tempo_contagem >= 5000)){
    Serial.println("Gerador LIGADO");
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Ger.: LIGADO");
    gerador_ligado = true;
  }

  if (gerador_ligado == true and leitura == LOW and monitorando_barulho == true){
    Serial.println("Contagem para desligar...");
    tempo_contagem = millis();
    gerador_desligando = true;
    monitorando_barulho = false;
    mensagem("Contagem para desligar...");
  }

  if (gerador_desligando == true and (millis() - tempo_contagem >= 5000)){
    Serial.println("Gerador DESLIGOU");
    gerador_ligado = false;
    monitorando_barulho = false;
    gerador_desligando = false;
    mensagem("Gerador DESLIGOU.");
  }

  lcd.setCursor(0,1);
  lcd.print("Temp:       C");
  lcd.setCursor(6,1);
  lcd.print(T);
 
}

