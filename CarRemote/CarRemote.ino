#define TIMEOUT 1000
#define SPEEDCHANGE 20

#include <AFMotor.h>
#include <SoftwareSerial.h>
bool forward,backward,turnleft,turnright,brake;
int speed, timeout;


SoftwareSerial SerialPort(10,9);
AF_DCMotor right(3);
AF_DCMotor left(4);

void setup() {
  SerialPort.begin(115200);
  SerialPort.println("Hello!");
  forward = false;
  backward = false;
  turnleft = false;
  turnright = false;
  speed = 200;
  right.setSpeed(speed);
  left.setSpeed(speed);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(SerialPort.available()>0){
    char text = SerialPort.read();
    switch(text){
      case 'a':
      forward = true;
      timeout = millis();
      break;
      case 'b':
      forward = false;
      break;
      case 'c':
      backward = true;
      timeout = millis();
      break;
      case 'd':
      backward = false;
      break;
      case 'e':
      turnleft = true;
      timeout = millis();
      break;
      case 'f':
      turnleft = false;
      break;
      case 'g':
      turnright = true;
      timeout = millis();
      break;
      case 'h':
      turnright = false;
      break;
      case 'i':
      if(speed >= 240){
        speed = 240;
      } else {
        speed += SPEEDCHANGE;
      }
      right.setSpeed(speed);
      left.setSpeed(speed);
      SerialPort.println(speed);
      break;
      case 'j':
      if(speed <= 0){
        speed = 0;
      } else {
        speed -= SPEEDCHANGE;
      }
      right.setSpeed(speed);
      left.setSpeed(speed);
      SerialPort.println(speed);
      break;
      case 'k':
      brake = true;
      timeout = millis();
      break;
      case 'l':
      brake = false;
      break;
    }
  }
  if(forward || backward || turnleft || turnright || brake){
    if((millis()-timeout) > TIMEOUT){
      forward = false;
      backward = false;
      turnright = false;
      turnleft = false;
      brake = false;
    }
  }
  if(forward){
    right.run(FORWARD);
    left.run(FORWARD);
  }
  if(backward){
    right.run(BACKWARD);
    left.run(BACKWARD);
  }
  if(turnleft){
    right.run(FORWARD);
    left.run(BACKWARD);
  }
  if(turnright){
    right.run(BACKWARD);
    left.run(FORWARD);
  }
  if(brake){
    right.run(BRAKE);
    left.run(BRAKE);
  }
  if(not(forward||backward||turnleft||turnright||brake)){
    right.run(RELEASE);
    left.run(RELEASE);
  }
}
