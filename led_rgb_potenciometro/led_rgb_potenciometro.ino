/*
 * LED RGB - cores controladas por Potenciômetros
 * Jhonathan. Banczek
 * github.com/jhoonb
 */

#define RED 3
#define BLUE 5
#define GREEN 6

const int pinoPOT0 = A0; // pino de entrada do potenciômetro BLUE
const int pinoPOT1 = A1; // pino de entrada do potenciômetro GREEN
const int pinoPOT2 = A2; // pino de entrada do potenciômetro RED

int valorRED = 0;
int valorGREEN = 0;
int valorBLUE = 0;

void setup() {
  pinMode(pinoPOT2, INPUT);
  pinMode(pinoPOT1, INPUT); 
  pinMode(pinoPOT0, INPUT);
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
  // testar antes se o maximo da 255 [+ 10]
  valorRED = map(analogRead(pinoPOT2), 0, 1023, 0, 265); 
  valorGREEN = map(analogRead(pinoPOT1), 0, 1023, 0, 265); //
  valorBLUE = map(analogRead(pinoPOT0), 0, 1023, 0, 265); //

  // verifica o limite
  valorRED = limite(valorRED);
  valorGREEN = limite(valorGREEN);
  valorBLUE = limite(valorBLUE);

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