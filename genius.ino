//Tamanho máximo da sequência
#define max_tam_sequencia 100

//Definição dos leds
#define led_verde 11
#define led_vermelho 10
#define led_azul 9
#define led_amarelo 8

//Definição dos botões
#define btn_amarelo 2
#define btn_azul 3
#define btn_vermelho 4
#define btn_verde 5

//Definição do inicio e fim dos loops dos leds
#define inicio_leds 8
#define fim_leds 11

int vet_sequencia_original[max_tam_sequencia], vet_sequencia_jogador[max_tam_sequencia]; //vetor de sequência
int tamanho_atual_da_sequencia, ultimo_sorteado = 0;
int posicao_vet;

void apagarLeds(){
  for(int i = inicio_leds; i <= fim_leds; ++i){
    digitalWrite(i, LOW);
  }
}

void definirLeds(){
  for(int i = inicio_leds; i <= fim_leds; ++i){
    pinMode(i, OUTPUT);
  }
}

void definirBotoes(){
  for(int i = 2; i <= 5; ++i){
    pinMode(i, INPUT_PULLUP);
  }
}

void iniciarSementeRandomica(){
  /* Se o pino de entrada analógica 0 é deixado desconectado,
   o ruído aleatório analógico irá causar a chamada de randomSeed()
   gerar sementes aleatórias diferentes cada vez que o sketch roda.
   randomSeed() basicamente "embaralha" a função random(). */
  randomSeed(analogRead(0));
}

void setup() {
  definirLeds(); //Define todos os leds como saída
  definirBotoes();//Define todos os botões como entrada
  apagarLeds();//Garante que todos os leds comecem apagados
  tamanho_atual_da_sequencia = 1;
  iniciarSementeRandomica();
}

void gerarSequencia(){
    int sorteado;
    do{
     sorteado = random(8, 12);
    }while(ultimo_sorteado == sorteado);
    ultimo_sorteado = sorteado;
    vet_sequencia_original[tamanho_atual_da_sequencia-1] = sorteado;//Gera um número aleatório de 8 a 11
}

void mostrarSequencia(){
  for(int i = 0; i < tamanho_atual_da_sequencia; ++i){
    digitalWrite(vet_sequencia_original[i], HIGH);
    delay(500);
    digitalWrite(vet_sequencia_original[i], LOW);
    delay(500);
  }
}

void apagarTodosLedsExceto(int aceso){
  for(int i = inicio_leds; i <= fim_leds; ++i){
    if(i != aceso){
      digitalWrite(i, LOW);
    }
    else{
      digitalWrite(i, HIGH);
    }
  }
}

void preencherVetSequenciaJogador(){
  posicao_vet = 0;
  do{
    if(!digitalRead(btn_amarelo)){
      delay(250);
      apagarTodosLedsExceto(led_amarelo);
      vet_sequencia_jogador[posicao_vet] = led_amarelo;
      posicao_vet++;
    }
    else if(!digitalRead(btn_azul)){
      delay(250);
      apagarTodosLedsExceto(led_azul);
      vet_sequencia_jogador[posicao_vet] = led_azul;
      posicao_vet++;
    }
    else if(!digitalRead(btn_vermelho)){
      delay(250);
      apagarTodosLedsExceto(led_vermelho);
      vet_sequencia_jogador[posicao_vet] = led_vermelho;
      posicao_vet++;
    }
    else if(!digitalRead(btn_verde)){
      delay(250);
      apagarTodosLedsExceto(led_verde);
      vet_sequencia_jogador[posicao_vet] = led_verde;
      posicao_vet++;
    }
  }while(posicao_vet < tamanho_atual_da_sequencia);
  delay(500);
}

bool sequenciaJogadorIgualSequenciaOriginal(){
  for(int i = 0; i < tamanho_atual_da_sequencia; ++i){
    if(vet_sequencia_jogador[i] != vet_sequencia_original[i]){
      return false;//O jogador errou
    }
  }
  return true;//O jogador acertou
}

void piscarLeds(){
    digitalWrite(led_vermelho, HIGH);
    digitalWrite(led_azul, HIGH);
    digitalWrite(led_verde, HIGH);
    digitalWrite(led_amarelo, HIGH);
    delay(200);
    digitalWrite(led_vermelho, LOW);
    digitalWrite(led_azul, LOW);
    digitalWrite(led_verde, LOW);
    digitalWrite(led_amarelo, LOW);
    delay(200);
}

bool apertouQualquerBotao(){
  if(!digitalRead(btn_amarelo) || !digitalRead(btn_vermelho) || !digitalRead(btn_azul) || !digitalRead(btn_verde)){
    return true;
  }
  return false;
}

void loop() {
  gerarSequencia();
  mostrarSequencia();
  apagarLeds();
  preencherVetSequenciaJogador();
  apagarLeds();
  delay(1000);
  if(!(sequenciaJogadorIgualSequenciaOriginal())){
    tamanho_atual_da_sequencia = 1;
    while(!apertouQualquerBotao()){
      piscarLeds();//Perdeu
    }
    delay(1000);
  }
  else{
    tamanho_atual_da_sequencia++;
  }
}
