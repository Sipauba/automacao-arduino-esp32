int a = 14;
int b = 16;
int c = 8;
int d = 7;
int e = 6;
int f = 15;
int g = 18;
int dp = 9;

int receptor = 4;

int contador = 0;

//int intervalo = 500;

void setup() {

  Serial.begin(9600);
  
  pinMode (a,OUTPUT);
  pinMode (b,OUTPUT);
  pinMode (c,OUTPUT);
  pinMode (d,OUTPUT);
  pinMode (e,OUTPUT);
  pinMode (f,OUTPUT);
  pinMode (g,OUTPUT);
  pinMode (dp,OUTPUT);

  pinMode(receptor, INPUT_PULLUP);
}

void zero(){
  digitalWrite(a,1);
  digitalWrite(b,1);
  digitalWrite(c,1);
  digitalWrite(d,1);
  digitalWrite(e,1);
  digitalWrite(f,1);
  digitalWrite(g,0);
}
void um(){
  digitalWrite(a,0);
  digitalWrite(b,1);
  digitalWrite(c,1);
  digitalWrite(d,0);
  digitalWrite(e,0);
  digitalWrite(f,0);
  digitalWrite(g,0);
}
void dois(){
  digitalWrite(a,1);
  digitalWrite(b,1);
  digitalWrite(c,0);
  digitalWrite(d,1);
  digitalWrite(e,1);
  digitalWrite(f,0);
  digitalWrite(g,1);
}
void tres(){
  digitalWrite(a,1);
  digitalWrite(b,1);
  digitalWrite(c,1);
  digitalWrite(d,1);
  digitalWrite(e,0);
  digitalWrite(f,0);
  digitalWrite(g,1);
}
void quatro(){
  digitalWrite(a,0);
  digitalWrite(b,1);
  digitalWrite(c,1);
  digitalWrite(d,0);
  digitalWrite(e,0);
  digitalWrite(f,1);
  digitalWrite(g,1);
}
void cinco(){
  digitalWrite(a,1);
  digitalWrite(b,0);
  digitalWrite(c,1);
  digitalWrite(d,1);
  digitalWrite(e,0);
  digitalWrite(f,1);
  digitalWrite(g,1);
}
void seis(){
  digitalWrite(a,1);
  digitalWrite(b,0);
  digitalWrite(c,1);
  digitalWrite(d,1);
  digitalWrite(e,1);
  digitalWrite(f,1);
  digitalWrite(g,1);
}
void sete(){
  digitalWrite(a,1);
  digitalWrite(b,1);
  digitalWrite(c,1);
  digitalWrite(d,0);
  digitalWrite(e,0);
  digitalWrite(f,0);
  digitalWrite(g,0);
}
void oito(){
  digitalWrite(a,1);
  digitalWrite(b,1);
  digitalWrite(c,1);
  digitalWrite(d,1);
  digitalWrite(e,1);
  digitalWrite(f,1);
  digitalWrite(g,1);
}
void nove(){
  digitalWrite(a,1);
  digitalWrite(b,1);
  digitalWrite(c,1);
  digitalWrite(d,1);
  digitalWrite(e,0);
  digitalWrite(f,1);
  digitalWrite(g,1);
}

void loop() {



  Serial.print(contador);

  if (digitalRead(receptor) == LOW){
    
    if (contador == 0){
      zero();
    }
    if (contador == 1){
      um();
    }
    if (contador == 2){
      dois();
    }
    if (contador == 3){
      tres();
    }
    if (contador == 4){
      quatro();
    }
    if (contador == 5){
      cinco();
    }
    if (contador == 6){
      seis();
    }
    if (contador == 7){
      sete();
    }
    if (contador == 8){
      oito();
    }
    if (contador == 9){
      nove();
    }
    if (contador == 10){
      contador = 0;
    }
  }
  if (digitalRead(receptor) == HIGH){
    contador = contador +1;
    if (contador == 10){
      contador = 0;
    }
    delay(400);
  }
}


  /*
  if (digitalRead(receptor) == HIGH){
    digitalWrite(dp,0);
  }
  if (digitalRead(receptor) == LOW){
    digitalWrite(dp,1);
  }
  */
  /*
  zero();
  delay(intervalo);
  um();
  delay(intervalo);
  dois();
  delay(intervalo);
  tres();
  delay(intervalo);
  quatro();
  delay(intervalo);
  cinco();
  delay(intervalo);
  seis();
  delay(intervalo);
  sete();
  delay(intervalo);
  oito();
  delay(intervalo);
  nove();
  delay(intervalo);
  */
  
