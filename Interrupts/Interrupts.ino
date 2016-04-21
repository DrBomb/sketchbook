#define MAXTIME 8333
#define TRIACPIN 6
#define POTPIN A0
#define DELAYPIN A1
#define CONTROLPIN A4
#define DEBUG false
int time, pulsewidth;
bool flag = false;

void setup() {
  // put your setup code here, to run once:
  pinMode(CONTROLPIN,INPUT);
  pinMode(POTPIN,INPUT);
  pinMode(TRIACPIN,OUTPUT);
  pinMode(DELAYPIN,INPUT);
  pinMode(2,INPUT);
  attachInterrupt(digitalPinToInterrupt(2), zero, RISING); 
  time = 4166;
  pulsewidth = 100;
  if(DEBUG){
    Serial.begin(9600);
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  if(digitalRead(CONTROLPIN) == HIGH && flag == false){
    pulsewidth = map(analogRead(DELAYPIN),0,1023,0,5000);
    time = map(analogRead(POTPIN),0,1023,0,MAXTIME-(pulsewidth+100));
  }
  if(DEBUG){
    Serial.print(time);
    Serial.print(" ");
    Serial.println(pulsewidth);
    delay(1);
  }
  if(flag == true){
    delayMicroseconds(time);
    digitalWrite(TRIACPIN,HIGH);
    delayMicroseconds(pulsewidth);
    digitalWrite(TRIACPIN,LOW);
    flag = false;
  }
}

void zero(){
  flag = true;
}
