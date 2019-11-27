/*
   Semaforos - simples
   Controle de 2 semáfaros de trânsito
   github.com/jhoonb - 2019
*/


int se1Vermelho = 13;
int se1Amarelo = 12;
int se1Verde = 11;
int se2Verde = 2;
int se2Amarelo = 3;
int se2Vermelho = 4;

void setup() {
  pinMode(se1Vermelho, OUTPUT);
  pinMode(se1Amarelo, OUTPUT);
  pinMode(se1Verde, OUTPUT);
  pinMode(se2Verde, OUTPUT);
  pinMode(se2Amarelo, OUTPUT);
  pinMode(se2Vermelho, OUTPUT);
}

void loop() {

  // sinal vermelho 1 -> sinal verde 2
  digitalWrite(se1Amarelo, LOW); // semaforo 1
  digitalWrite(se1Vermelho, HIGH); // semaforo 1
  digitalWrite(se1Verde, LOW); // semaforo 1

  digitalWrite(se2Verde, HIGH);// semaforo 2
  digitalWrite(se2Amarelo, LOW); // semaforo 2
  digitalWrite(se2Vermelho, LOW); // semaforo 2
  delay(5000);

  // sinal amarelo
  digitalWrite(se2Verde, LOW);// semaforo 2

  for (int i = 0; i < 8; i++) {
    digitalWrite(se2Amarelo, HIGH); // semaforo 2
    delay(300);
    digitalWrite(se2Amarelo, LOW); // semaforo 2
    delay(300);
  }
  digitalWrite(se2Amarelo, LOW); // semaforo 2
  digitalWrite(se2Vermelho, LOW); // semaforo 2
  //delay(3000);

  // repete outro semafaro
  // sinal vermelho 1 -> sinal verde 2
  digitalWrite(se2Amarelo, LOW); // semaforo 1
  digitalWrite(se2Vermelho, HIGH); // semaforo 1
  digitalWrite(se2Verde, LOW); // semaforo 1

  digitalWrite(se1Verde, HIGH);// semaforo 2
  digitalWrite(se1Amarelo, LOW); // semaforo 2
  digitalWrite(se1Vermelho, LOW); // semaforo 2
  delay(5000);

  // sinal amarelo
  digitalWrite(se1Verde, LOW);// semaforo 2

  for (int i = 0; i < 8; i++) {
    digitalWrite(se1Amarelo, HIGH); // semaforo 2
    delay(300);
    digitalWrite(se1Amarelo, LOW); // semaforo 2
    delay(300);
  }
  digitalWrite(se1Amarelo, LOW); // semaforo 2

  digitalWrite(se1Vermelho, LOW); // semaforo 2
}