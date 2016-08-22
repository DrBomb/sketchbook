
#include <FastLED.h>
#include "font8x8_basic.h"
#define NUM_LEDS 512
#define DATA_PIN 17
#define MATRIX_OFFSET 0
const int reversed[8] = {7,6,5,4,3,2,1,0};
CHSV LetterColor(0,255,60);
CRGB leds[NUM_LEDS];
void setup() {
  FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds,NUM_LEDS);
  //FastLED.setBrightness(30);
  FastLED.show();
}

void loop() {
  // put your main code here, to run repeatedly:
  String Nombre = "Juan";
  mostrar(LetterColor,Nombre);
  LetterColor.hue++;
  FastLED.show();
  delay(10);
  /*Serial.print(((int)'a' - 32) * 7);
  Serial.print(" ");
  Serial.println(Font7x7[((int)'a'-32)*7],HEX);
  delay(3000);*/
}

void mostrar(CHSV color, String Nombre){
  char ing[5] = "Ing";
  for(int i = 0;i<sizeof(ing)-1;i++){
    for(int x = 0;x<8;x++){
      for(int y = 0;y<8;y++){
        if(bitRead(font8x8_basic[(int)ing[i]][y],x)==1){
          leds[Matrix((i*8)+x+5,y)] = color;
        } else {
          leds[Matrix((i*8)+x+5,y)] = CRGB::Black;
        }
      }
    }
  }
  for(int i = 0;i<Nombre.length();i++){
    for(int x = 0;x<8;x++){
      for(int y = 0;y<8;y++){
        if(bitRead(font8x8_basic[(int)Nombre.charAt(i)][y],x)==1){
          leds[Matrix((i*8)+x,y+8)] = color;
        } else {
          leds[Matrix((i*8)+x,y+8)] = CRGB::Black;
        }
      }
    }
  }
}

int Matrix(unsigned int x, unsigned int y){
  if(y>15){
    y=15;
  }
  if(x>32){
    x=32;
  }
  int Led;
  if(y<8){
    if(x%2 == 0){
      Led = MATRIX_OFFSET + (x*8) + y;
    } else {
      Led = MATRIX_OFFSET + (x*8) + reversed[y];
    }
  } else {
    if(x%2 == 0){
      Led = MATRIX_OFFSET + 511 - (x*8) - reversed[y-8];
    } else {
      Led = MATRIX_OFFSET + 511 - (x*8) - (y-8);
    }
  }
  return Led;
}


