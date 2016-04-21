// Muestra la direccion de IP al enviarle un caracter al puerto serial.

void setup() {
  Serial.begin(9600);
  while(!Serial.available()){
  }
  system("ifconfig > /dev/ttyGS0");
}

void loop() {
  // put your main code here, to run repeatedly:

}
