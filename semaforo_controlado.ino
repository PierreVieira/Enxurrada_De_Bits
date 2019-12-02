#define pedestre_verde 6
#define pedestre_vermelho 7
#define carro_verde 13
#define carro_amarelo 9
#define carro_vermelho 10
#define botao 12
#define buzina 11
#define tempo_espera1 1000
#define tempo_espera2 (tempo_espera1)/2

void estados();

void apagarLeds(){
  digitalWrite(carro_verde, LOW);
  digitalWrite(carro_amarelo, LOW);
  digitalWrite(carro_vermelho, LOW);
  digitalWrite(pedestre_verde, LOW);
  digitalWrite(pedestre_vermelho, LOW);
}
void setup(){
	pinMode(pedestre_verde, OUTPUT);
  	pinMode(pedestre_vermelho, OUTPUT);
  	pinMode(carro_verde, OUTPUT);
    pinMode(carro_amarelo, OUTPUT);
    pinMode(carro_vermelho, OUTPUT);
    pinMode(buzina, OUTPUT);
  	pinMode(botao, INPUT_PULLUP);
}

bool apertouBotao(){
	return !digitalRead(botao);
}

bool myDelay(int time){
  for(int i = 0; i < time; ++i){
    if(apertouBotao()){
      tone(buzina, 239, 200);
		return true;    
    }
    delay(1);
  }
  return false;
}

void desligarBuzina(){
	noTone(buzina);
}

void primeiroEstado(){
  apagarLeds();
  //Acesos: vermelho para o carro e verde para o pedestre
  digitalWrite(carro_vermelho, HIGH);
  digitalWrite(pedestre_verde, HIGH);
  delay(tempo_espera1);
}

void segundoEstado(){
  apagarLeds();
  //Acesos: amarelo para o carro e vermelho para o pedestre
  digitalWrite(carro_amarelo, HIGH);
  digitalWrite(pedestre_vermelho, HIGH);
  if(myDelay(tempo_espera2)){
  	estados();
  }
}

void terceiroEstado(){
  apagarLeds();
  //Acesos: verde para o carro e vermelho para o pedestre
  digitalWrite(carro_verde, HIGH);
  digitalWrite(pedestre_vermelho, HIGH);
  if(myDelay(tempo_espera1)){
  	estados();
  }
}

void estados(){
  apagarLeds();
  primeiroEstado();
  segundoEstado();
  terceiroEstado();
}

void loop(){
  estados();
}
