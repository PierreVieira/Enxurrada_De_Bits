#define potenciometro A0
#define inicio 2
#define fim 7
#define min_time 20
#define max_time 2000

int valor_pot, time_delay;//O tempo do delay está em milisegundos 
void defineLedsComoSaida(){
  //Essa função vai definir todos os leds como saída
  for(int i = inicio; i <= fim; ++i){
    pinMode(i, OUTPUT);   
  }
}

void setup(){
  defineLedsComoSaida();  
}

void myDelay(){ 
  valor_pot = analogRead(potenciometro);
  time_delay = map(valor_pot, 0, 1023, min_time, max_time);
  delay(time_delay);
}

void piscarGalera(){
  for(int i = inicio; i <= fim; ++i){
    digitalWrite(i, HIGH);
    myDelay();  
    digitalWrite(i, LOW);
    myDelay();
  }
}
void loop(){
  piscarGalera();
}
