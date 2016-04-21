// Controlling a servo position using a potentiometer (variable resistor) 
// by Michal Rinott <http://people.interaction-ivrea.it/m.rinott> 
// Traducido por Juan Molero

#include <Servo.h> 
 
Servo myservo;  // create servo object to control a servo 
 
int potpin = 0;  // Pin analogico donde sera conectado el potenciometro
int val;    // Variable para leer el valor del pin analogico
 
void setup() 
{ 
  myservo.attach(9);  // conecta el pin 9 al objeto de servo
} 
 
void loop() 
{ 
  val = analogRead(potpin);            // Lee el valor del potenciometro (Entre 0 y 1023)
  val = map(val, 0, 1023, 0, 179);     // Le aplicamos escalamiento para usarlo con el servo (un valor entre 0 y 180)
  myservo.write(val);                  // Coloca al servo en la posicion indicada por el valor escalado
  delay(15);                           // Espera que el servo llegue a su destino
} 
