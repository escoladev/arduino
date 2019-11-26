/*
 * LED RGB - cores controladas por Potenciômetros
 * Jhonathan. Banczek
 * github.com/jhoonb
 */

#define RED 3
#define BLUE 5
#define GREEN 6

int valorRED = 0;
int valorGREEN = 0;
int valorBLUE = 0;

void setup() {
  pinMode(RED, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(BLUE, OUTPUT);
  Serial.begin(9600);

}

/*
 * limite: função que retorna o valor máximo 255
 * se o valor recebido pelo potenciômetro 
 * for igual ou maior a 253.
 * [apenas para limite e teste do potenciômetro, depende do resistor]
 */
int limite(int vcor) {
  if(vcor >= 255) {
    return 255;
  }
  return vcor;
}


void loop() {

  valorRED = 200;
  valorGREEN = 200;
  valorBLUE = 50;

  // exibir no Monitor Serial
  Serial.print("valorRED: ");
  Serial.print(valorRED);
  Serial.print("       valorGREEN: ");
  Serial.print(valorGREEN);
  Serial.print("       valorBLUE: ");
  Serial.println(valorBLUE);
  
  // seta os valores no led
  analogWrite(RED, valorRED);
  analogWrite(GREEN, valorGREEN);
  analogWrite(BLUE, valorBLUE);
  
  // pode ajustar, quanto menor o valor, 
  // maior 'precisão' no potenciômetro
  delay(10);
}
