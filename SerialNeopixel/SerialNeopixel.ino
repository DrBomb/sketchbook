#include <SoftwareSerial.h>
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

#define PIN 6

#define NUM 5

int pointer = 0;
int packet[3];
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUM, PIN, NEO_GRB + NEO_KHZ800);
void setup() {
  Serial.begin(9600);
  pixels.begin();
  for(int x = 0;x<NUM;x++){
    pixels.setPixelColor(x,pixels.Color(0,0,0));
  }
  pixels.show();
}

void loop() {
  if(Serial.available()){
    char command = Serial.read();
    int color1,color2,color3;
    switch(command){
      case 'c':
      color1 = Serial.parseInt();
      color2 = Serial.parseInt();
      color3 = Serial.parseInt();
      for(int x = 0;x<NUM;x++){
        pixels.setPixelColor(x,pixels.Color(color1,color2,color3));
      }
      pixels.show();
      pointer = 0;
      break;
      case 's':
      color1 = Serial.parseInt();
      color2 = Serial.parseInt();
      color3 = Serial.parseInt();
      pixels.setPixelColor(pointer,pixels.Color(color1,color2,color3));
      pixels.show();
      pointer++;
      if(pointer == 5){
        pointer = 0;
      }
      break;
    }
  }
}
