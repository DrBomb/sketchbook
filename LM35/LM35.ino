float base;

void setup() {
  Serial.begin(9600);
  pinMode(A0,INPUT);
}

void loop() {
  Serial.println(analogRead(A0)/2);
  delay(1000);

}
