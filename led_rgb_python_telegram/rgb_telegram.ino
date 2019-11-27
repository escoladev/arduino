/*
   Arduino - LED RGB Cores
   Será controlado via Python
   @github.com/jhoonb
   [Carregar este programa no arduino].
*/

char  serialData;

//check always the pins
int redPin = 4;
int greenPin = 3;
int bluePin = 2;


void setup()
{
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  Serial.begin(9600);
}

void loop() {

  int valoareIluminare = analogRead(0);
  Serial.println(valoareIluminare, DEC);
  delay(100);

  if (Serial.available() > 0) {

    serialData = Serial.read();
    Serial.print(serialData);

    switch (serialData) {
      case '0': // Branco
        setColor(255, 255, 255);
        break;
      case '1': // Azul
        setColor(0, 0, 255);
        break;
      case '2': // Vermelho
        setColor(255, 0, 0);
        break;
      case '3': // Verde
        setColor(0, 255, 0);
        break;
      case '4': // Amarelo
        setColor(255, 255, 0);
        break;
      case '5': // Magenta
        setColor(255, 0, 255);
        break;
      case '6': // Ciano
        setColor( 0, 255, 255);
        break;
      case '7': // Preto
        setColor( 0, 0, 0);
        break;
      default:
        Serial.println("sem cor definida");
        break;
    }
  }
}
void setColor(int redValue, int greenValue, int blueValue) {
  analogWrite(redPin, redValue);
  analogWrite(greenPin, greenValue);
  analogWrite(bluePin, blueValue);
}