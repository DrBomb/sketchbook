
#include <FastLED.h>
#include "font7x7.h"
#define NUM_LEDS 512
#define DATA_PIN 17
#define MATRIX_OFFSET 0
CRGB leds[NUM_LEDS];
void setup() {
  FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds,NUM_LEDS);
  leds[Matrix(0,0)] = CRGB::White;
  leds[Matrix(1,0)] = CRGB::Blue;
  leds[Matrix(0,8)] = CRGB::Red;
  FastLED.show();
  
}

void loop() {
  // put your main code here, to run repeatedly:

}
int Matrix(int x, int y){
  const int reversed[8] = {7,6,5,4,3,2,1,0};
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


