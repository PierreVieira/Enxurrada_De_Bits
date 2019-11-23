


int carRed = 12;// PIERE CAMADA FECHADO 10 a 10
int carYellow = 11;
int carGreen = 10;
int pedRed = 8;
int pedGreen = 9;
int button = 2;
int crossTime = 5000;
unsigned long changeTime;


void setup() {
  pinMode(carRed, OUTPUT);
  pinMode(carYellow, OUTPUT);
  pinMode(carGreen, OUTPUT);
  pinMode(pedRed, OUTPUT);
  pinMode(pedGreen, OUTPUT);
  pinMode(button, INPUT);

  digitalWrite(carGreen, HIGH); //Iniciar aceso,Green do carro
  digitalWrite(pedRed, HIGH); // Iniciar aceso, Red do Predestre
}

void loop() {
  int state = digitalRead(button);// state do botao

  if (state == HIGH && (millis() - changeTime) > 2000) {
    changeLights();
  }

  if (millis() - changeTime >7000) {
    changeLights();
  }
}

void changeLights() {
  digitalWrite(carGreen, LOW);
  digitalWrite(carYellow, HIGH);
  delay(1000);
  digitalWrite(carYellow, LOW);
  digitalWrite(carRed, HIGH);
  delay(500);
  digitalWrite(pedRed, LOW);
  digitalWrite(pedGreen, HIGH);
  delay(crossTime);

  for (int x=0; x<5; x++){
    digitalWrite(pedGreen, HIGH);
    delay(250);
    digitalWrite(pedGreen, LOW);
    delay(250);
  }

  digitalWrite(pedRed, HIGH);
  delay(500);
  digitalWrite(carYellow, LOW);
  delay(500);
  digitalWrite(carRed, LOW);
  delay(1000);
  digitalWrite(carGreen, HIGH);
  digitalWrite(carYellow, LOW);
  digitalWrite(carRed, LOW);
  
  changeTime = millis();
}
