// Sweep
// by BARRAGAN <http://barraganstudio.com> 
// This example code is in the public domain.
// Traducido por Juan Molero
// El servo conectado va de 0 grados a 180 grados y regresa


#include <Servo.h>

Servo myservo;  // Crea un objeto servo para controlar un servomotor 
                // Un maximo de 8 servos pueden ser creados
 
int pos = 0;    // variable para guardar la posicion del servo 

void setup() 
{ 
  myservo.attach(9);  // Conecta el objeto servo al pin 9
} 
 
 
void loop() 
{ 
  for(pos = 0; pos < 180; pos += 1)  // de 0 grados a 180 grados
  {                                  // en pasos de 1 grado
    myservo.write(pos);              // decirle al servo que vaya a la posicion indicada en 'pos'
    delay(15);                       // espera 15ms para que el servo llegue a su posicion
  } 
  for(pos = 180; pos>=1; pos-=1)     // del 180 grados a 0 grados 
  {                                
    myservo.write(pos);              // ordenar al servo que vaya a la posicion indicada en 'pos'
    delay(15);                       // espera 15ms para que el servo llegue a su posicion 
  } 
} 
