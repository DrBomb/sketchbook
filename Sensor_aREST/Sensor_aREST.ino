#include <SPI.h>
#include <UIPEthernet.h>
#include <aREST.h>
#include <avr/wdt.h>

byte mac[] = { 0x90, 0xA2, 0xDA, 0x0E, 0xFE, 0x40 };

IPAddress ip(192,168,2,2);

EthernetServer server(80);

aREST rest = aREST();

int temperatura;
int humedad[3];

void setup() {
  // put your setup code here, to run once:
  pinMode(A0, OUTPUT);
  pinMode(A5,INPUT);
  temperatura = 24;
  humedad[0] = 40;
  humedad[1] = 30;
  humedad[2] = 35;
  rest.variable("temp",&temperatura);
  rest.variable("hum0",&humedad[0]);
  rest.variable("hum1",&humedad[1]);
  rest.variable("hum2",&humedad[2]);
  rest.function("act",actualizarSensores);
  rest.function("bomb",controlBomba);
  rest.set_id("1");
  rest.set_name("1");
  if (Ethernet.begin(mac) == 0) {
    Ethernet.begin(mac, ip);
  }
  server.begin();
  // Start watchdog
  wdt_enable(WDTO_4S);
}

void loop() {
  // put your main code here, to run repeatedly:
  // listen for incoming clients
  EthernetClient client = server.available();
  rest.handle(client);
  wdt_reset();
}

int controlBomba(String command){
  int estado = command.toInt();
  digitalWrite(A0,estado);
  return estado;
}

int actualizarSensores(String command){
  humedad[0] = 90; //calcular Humedad 1
  humedad[1] = 80; //calcular Humedad 2
  humedad[2] = 70; //calcular humedad 3
  temperatura = analogRead(A5)/2;
  return 1;
}
