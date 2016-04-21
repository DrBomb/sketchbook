#include <SoftwareSerial.h>

void setup() {
  Serial.begin(9600);
  for(int x=0;x<=255;x++){
    Serial.write(x);
    Serial.print(" ");
    Serial.println(x);
  }
}

void loop() {
  if(Serial.available()){
    char chr = Serial.read();
    Serial.print(chr);
    Serial.print(" ");
    Serial.println((int)chr & 0xFF);
    }
}
