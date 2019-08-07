int sequencia[20] = {};
int botoes[4] = {8, 9, 10, 11};
int leds[4] = {2, 3, 4, 5};
int rodada = 0;
int passo = 0;
int botao_pressionado = 0;
int game_over = 0;
int errou = 0;
int vitoria = 0;

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);

  pinMode(8, INPUT_PULLUP);
  pinMode(9, INPUT_PULLUP);
  pinMode(10, INPUT_PULLUP);
  pinMode(11, INPUT_PULLUP);
  Serial.begin(9600);
  randomSeed(45);

}

// the loop function runs over and over again forever
void loop() {
  proximaRodada();
  reproduzirSequencia();
  aguardarJogador();
  if (game_over == 3) {
    sequencia[20] = {};
    rodada = 0;
    passo = 0;
    game_over = 0;
    errou = 0;
    vitoria = 0;
  }
  if(vitoria == 20){
    ganhou();
    sequencia[20] = {};
    rodada = 0;
    passo = 0;
    game_over = 0;
    errou = 0;
    vitoria = 0;
  }
  delay(1000);

}

void proximaRodada() {
  if (!errou == 1) {
    int sorteio = random(4);
    sequencia[rodada] = sorteio;
    rodada = rodada + 1;
    Serial.print(sorteio);
  }
}

void reproduzirSequencia() {
  for (int i = 0; i < rodada; i++) {
    digitalWrite(leds[sequencia[i]], HIGH);
    delay(500);
    digitalWrite(leds[sequencia[i]], LOW);
    delay(100);
  }
}

void aguardarJogador() {
  for (int i = 0; i < rodada; i++) {
    bool jogada_efetuada = false;
    while (!jogada_efetuada) {
      for (int i = 0; i <= 3; i++) {
        if (digitalRead(botoes[i]) == LOW) {
          botao_pressionado = i;
          digitalWrite(leds[i], HIGH);
          delay(300);
          digitalWrite(leds[i], LOW);
          jogada_efetuada = true;
        }
      }
    }
    // verificando a jogada
    if (sequencia[passo] != botao_pressionado) {
      // efeito que indica q ele errou
      for (int i = 0; i <= 3; i++) {
        digitalWrite(leds[i], HIGH);
        delay(100);
        digitalWrite(leds[i], LOW);
      }
      game_over++;
      if(errou == 1){
        
      }else{
        errou = 1;
      }
      
      break;
    }
    errou = 0;
    passo = passo + 1;
  }
  passo = 0;
  if(errou == 0){
   vitoria++; 
  }
}

void ganhou(){
  for (int i = 0; i <= 20; i++) {
        digitalWrite(leds[0], HIGH);
        digitalWrite(leds[1], HIGH);
        digitalWrite(leds[2], HIGH);
        digitalWrite(leds[3], HIGH);
        delay(100);
        digitalWrite(leds[0], LOW);
        digitalWrite(leds[1], LOW);
        digitalWrite(leds[2], LOW);
        digitalWrite(leds[3], LOW);
        delay(100);
        
      }
}

