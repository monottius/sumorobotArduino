#include <NECIRrcv.h> // Librería control remoto con infrarrojo.
#define Sensor_IR 11 // Se declara el pin 11 para el Sensor Infrarrojo
NECIRrcv ir(Sensor_IR);
//Declaración de pines a usar
int ENA = 5;
int ENB = 6;
/*IN1 E IN2 SON EL LADO DERECHO, IN1 HACIA ATRAS E IN2 HACIA ADELANTE
  IN3 E IN4 SON EL LADO IZQUIERDO, IN3 HACIA ATRAS E IN4 HACIA ADELANTE*/
int IN1 = 7;
int IN2 = 8;
int IN3 = 9;
int IN4 = 10;
int SCentro = 15;
int Valor = 0;
const int Echo = 12;
const int Trigger = 13;
int SensorIR = 11;
long t;
long d;
unsigned long ircode;

void setup() {
  // Se prepara la comunicación serial
  Serial.begin(9600);
  //Configurar los pines de entrada y salida
  pinMode(Echo, INPUT);
  pinMode(Trigger, OUTPUT);
  pinMode(SCentro, INPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(SensorIR, INPUT);
  ir.begin();
}

void loop()
{
  while (ir.available()) {
    ircode = ir.read();
    Serial.print("got code: 0x");
    Serial.println(ircode, HEX);
  }

  if (ircode == 0x6F905583 || ircode == 0xBF40FF00) { // Códigos infrarrojos e inicios del condicional if
    Ultrasonido();
    Valor = analogRead(SCentro);
    if (Valor >= 600) {
      retroceder(400, 255);
      Doblar_DER(600, 200);
    }
    if (Valor < 600); {
      if (d < 20) {
        avanzar(0, 200);
      }
      else {
        avanzar(0, 200);
      }
    }
  } // Cierre del if 


} // llave loop

//Funciones usadas en la programación
void avanzar(int tiempo, int velocidad) {
  analogWrite(ENA, velocidad);
  analogWrite(ENB, velocidad);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  delay(tiempo);

}
void retroceder(int tiempo, int velocidad)
{
  analogWrite(ENA, velocidad);
  analogWrite(ENB, velocidad);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  delay(tiempo);
}
void Doblar_DER(int tiempo, int velocidad)
{
  analogWrite(ENA, velocidad);
  analogWrite(ENB, velocidad);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  delay(tiempo);

}
void Doblar_IZQ(int tiempo, int velocidad)
{
  analogWrite(ENA, velocidad);
  analogWrite(ENB, velocidad);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  delay(tiempo);
}
void Frenar(int tiempo)
{
  analogWrite(ENA, 0);
  analogWrite(ENB, 0);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  delay(tiempo);
}
void Ultrasonido()
{
  digitalWrite(Trigger, LOW);
  delayMicroseconds(2);
  digitalWrite(Trigger, HIGH);
  delayMicroseconds(10);
  digitalWrite(Trigger, LOW);
  t = pulseIn(Echo, HIGH);
  d = t / 59;
  Serial.print(d);
  Serial.print(" cm ----");
  delay(100);
}
