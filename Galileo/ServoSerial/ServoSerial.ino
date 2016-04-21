// Creado por Juan Molero

#include <Servo.h>

Servo myservo; // Crea un objeto servo para controlar un servomotor 
               // Un maximo de 8 servos pueden ser creados
int pos = 0;   // variable para guardar la posicion del servo 

void setup() 
{ 
  Serial.begin(9600); // Inicia el puerto serial en 9600 baudios
  myservo.attach(9);  // Conecta el objeto servo al pin 9
} 

void loop() {
  if(Serial.available()){    // Espera a que llegue un caracter al puerto serial
    pos = Serial.parseInt(); // Convierte una cadena de caracteres a entero
    if(pos<0 || pos > 180){  // COnfirmar que el valor recibido es de un rango valido para el servo
      Serial.println("Valor Incorrecto");
    } else {
      myservo.write(pos);    // Mandar al servo a la posicion indicada
      delay(15);             // Esperar 15 ms a que llegue a la posicion
      while(Serial.available()){
        Serial.read();
      }
    }
  }

}
