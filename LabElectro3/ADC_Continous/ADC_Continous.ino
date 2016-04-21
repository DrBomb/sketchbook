#include <avr/interrupt.h>

#define MAXTIME 8333
#define PULSEWIDTH 100
#define TRIACPIN 6
#define ZEROPIN 2
#define POTPIN A0
volatile int delay_time;
volatile bool flag = false;

void setup() {
  Serial.begin(115200);
  pinMode(ZEROPIN,INPUT);
  pinMode(TRIACPIN,OUTPUT);
  pinMode(POTPIN,INPUT);
  ADMUX = 0b01000000;
  ADCSRA = 0b10101111;
  ADCSRB = 0b0;
  attachInterrupt(digitalPinToInterrupt(2), zero, RISING);
  sei();
  ADCSRA = 0b11101111;
}

void loop() {
  // put your main code here, to run repeatedly:
  if(flag == true){
    delayMicroseconds(delay_time);
    digitalWrite(TRIACPIN,HIGH);
    delayMicroseconds(PULSEWIDTH);
    digitalWrite(TRIACPIN,LOW);
    flag = false;
  }
}

ISR(ADC_vect){
  volatile int reading = (ADCH<<8) | ADCL;
  delay_time = map(reading,0,1023,0,MAXTIME-(PULSEWIDTH+50));
}

void zero(){
  flag = true;
}

