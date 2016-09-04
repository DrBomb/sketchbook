
#include <FastLED.h>
#include "font8x8_basic.h"
#include "Nombres.h"
#define NUM_LEDS 512
#define DATA_PIN 17
#define MATRIX_OFFSET 0
char Data[6];
const int reversed[8] = {7,6,5,4,3,2,1,0};
String Nombre;
CHSV LetterColor(0,255,60);
CRGB leds[NUM_LEDS];
void setup() {
  Serial.begin(9600);
  Nombre.reserve(12);
  random16_add_entropy(analogRead(0));
  FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds,NUM_LEDS);
  //FastLED.setBrightness(30);
  FastLED.show();
}

void loop() {
  // put your main code here, to run repeatedly:
  unsigned int index = random8(54);
  Serial.println(index);
  mostrarNombre(index);
  mostrarNombre(index);
  //LetterColor.hue++;
  //FastLED.show();
  delay(10);
  /*Serial.print(((int)'a' - 32) * 7);
  Serial.print(" ");
  Serial.println(Font7x7[((int)'a'-32)*7],HEX);
  delay(3000);*/
}

void mostrarNombre(int index){
  Nombre = String(Nombres[index]);
  Nombre.trim();
  for(unsigned int i = 0;i<Nombre.length()-4;i++){
    Data[0] = Nombre.charAt(i);
    Data[1] = Nombre.charAt(i+1);
    Data[2] = Nombre.charAt(i+2);
    Data[3] = Nombre.charAt(i+3);
    Data[4] = Nombre.charAt(i+4);
    for(unsigned int j = 0;j<9;j++){
      fiveScrollLeft(Data,j);
      LetterColor.hue++;
      FastLED.show();
      delay(50);
    }
  }
  delay(200);
  for(int i = 0;i<Nombre.length()-4;i++){
    char Data[6];
    Data[4] = Nombre.charAt(Nombre.length()-1-i);
    Data[3] = Nombre.charAt(Nombre.length()-2-i);
    Data[2] = Nombre.charAt(Nombre.length()-3-i);
    Data[1] = Nombre.charAt(Nombre.length()-4-i);
    Data[0] = Nombre.charAt(Nombre.length()-5-i);
    for(int j = 8;j>=0;j--){
      fiveScrollLeft(Data,j);
      LetterColor.hue++;
      FastLED.show();
      delay(50);
    }
  }
  delay(200);
}

void fiveScrollLeft(char Data[6], int pos){
  for(int x = 0;x<8-pos;x++){
    for(int y = 0;y<8;y++){
      if(bitRead(font8x8_basic[(int)Data[0]][y],x+pos)==1){
        leds[ Matrix(x,y+8) ]  = LetterColor;
      } else {
        leds[ Matrix(x,y+8) ] = CRGB::Black;
      }
    }
  }
  for(int x = 0;x<pos;x++){
    for(int y = 0;y<8;y++){
      if(bitRead(font8x8_basic[(int)Data[4]][y],x)==1){
        leds[ Matrix((8*4)-pos+x,y+8) ] = LetterColor;
      } else {
        leds[ Matrix((8*4)-pos+x,y+8) ] = CRGB::Black;
      }
    }
  }
  for(int i = 1;i<4;i++){
    for(int x = 0;x<8;x++){
      for(int y = 0;y<8;y++){
        if(bitRead(font8x8_basic[(int)Data[i]][y],x)==1){
          leds[Matrix((i*8)+x-pos,y+8)] = LetterColor;
        } else {
          leds[Matrix((i*8)+x-pos,y+8)] = CRGB::Black;
        }
      }
    }
  }
}
/*
void mostrar(CHSV color, String Nombre){
  char ing[5] = "Ing";
  for(unsigned int i = 0;i<sizeof(ing)-1;i++){
    for(int x = 0;x<8;x++){
      for(int y = 0;y<8;y++){
        if(bitRead(font8x8_basic[(int)ing[i]][y],x)==1){
          leds[Matrix((i*8)+x+5,y)] = LetterColor;
        } else {
          leds[Matrix((i*8)+x+5,y)] = CRGB::Black;
        }
      }
    }
  }
  for(unsigned int i = 0;i<Nombre.length();i++){
    for(int x = 0;x<8;x++){
      for(int y = 0;y<8;y++){
        if(bitRead(font8x8_basic[(int)Nombre.charAt(i)][y],x)==1){
          leds[Matrix((i*8)+x,y+8)] = LetterColor;
        } else {
          leds[Matrix((i*8)+x,y+8)] = CRGB::Black;
        }
      }
    }
  }
}
*/
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


