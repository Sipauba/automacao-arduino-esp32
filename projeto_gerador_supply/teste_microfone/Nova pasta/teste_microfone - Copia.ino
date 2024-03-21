#include <LiquidCrystal_I2C.h>

int lcdColunas = 16;
int lcdLinhas = 2;
LiquidCrystal_I2C lcd(0x27, lcdColunas, lcdLinhas);

static bool monitorando_barulho = false;
static bool gerador_ligado = false;

const int microfone = 15; // Porta D15 (GPIO15) para leitura analógica

unsigned long tempo_contagem = 0; // Variável para controlar o tempo de contagem

void setup() {
  pinMode(microfone, INPUT);
  Serial.begin(115200);
  lcd.init(); // Liga o display LCD
  lcd.backlight();
}

void loop() {
  int leitura = digitalRead(microfone);
  unsigned long tempo_atual = millis(); // Atualiza o tempo atual

  if (!monitorando_barulho && leitura == HIGH) {
    monitorando_barulho = true;
    Serial.println("Contagem para Ligar");
    tempo_contagem = tempo_atual; // Inicia a contagem de tempo
  } else if (monitorando_barulho && leitura == LOW) {
    monitorando_barulho = false;
    Serial.println("Cancelando contagem para Ligar");
    tempo_contagem = 0; // Zera a contagem de tempo
  }

  if (!gerador_ligado && monitorando_barulho && (tempo_atual - tempo_contagem >= 5000)) {
    gerador_ligado = true;
    Serial.println("Gerador Ligado");
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Ger.: LIGADO");
  } else if (gerador_ligado && !monitorando_barulho && (tempo_atual - tempo_contagem >= 5000)) {
    gerador_ligado = false;
    Serial.println("Gerador Desligado");
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Ger.: DESLIGADO");
  }

  delay(100); // Adiciona um pequeno atraso para estabilidade
}
