#include <SPI.h>
#include <UIPEthernet.h>
#include <UIPServer.h>
#include <UIPClient.h>
#include <avr/wdt.h>
EthernetServer server = EthernetServer(23);

byte mac[] = { 0x90, 0xA2, 0xDA, 0x0E, 0xFE, 0x40 };

IPAddress ip(192,168,2,2);

int pump = 0;

void setup() {
  Serial.begin(112500);
  pinMode(A0,OUTPUT);
  digitalWrite(A0,LOW);
  if (Ethernet.begin(mac) == 0) {
    Ethernet.begin(mac, ip);
  }
  server.begin();
  Serial.print(Ethernet.localIP());
  wdt_enable(WDTO_4S);
}

void loop() {
  if(EthernetClient client = server.available()){
    if(client){
      Serial.println("Conectado");
      char recibido;
      while(client.available()>0){
        recibido = client.read();
        switch(recibido){
          case 's':
          client.read();
          mostrarSensores(client);
          limpiarBuffer(client);
          break;
          case 'b':
          recibido = client.read();
          if(recibido == '1' || recibido == '0'){
            accionarBomba(recibido);
          } else {
            invalido(client);
          }
          limpiarBuffer(client);
          break;
          default:
          invalido(client);
          limpiarBuffer(client);
          break;
        }
      }
    }
  }
  wdt_reset();
}

void mostrarSensores(EthernetClient client){
  Serial.println("Sensores");
  String retorno;
  retorno = "{";
  retorno += temperatura();
  retorno += ",";
  retorno += humedades();
  retorno += ",";
  retorno += bomba();
  retorno += "}";
  client.println(retorno);
}

String temperatura(){
  //Aca va el Codigo para leer el LM·35
  //Son 10mV por ºC
  //El arduino tienen una resolucion de 10 bits
  //Que resulta en 5V/1024 = 0.00488
  //10mV / 0.00488 = 2.048
  //Aproximamos entonces la lectura a valor/2
  String regreso = "\"temperatura\":";
  float temp;
  temp = analogRead(A5)/2;
  regreso += String(temp,1);
  return regreso;
}

String humedades(){
  //Aca va el modo que lean la humedad
  //Veo que es simple asi que lo pondre como esta en el codigo
  int lectura,porcentaje;
  String regreso = "\"humedades\":[";
  lectura = analogRead(A4);
  porcentaje = map(lectura,0,1023,0,100);
  regreso += porcentaje;
  regreso += ",";
  lectura = analogRead(A3);
  porcentaje = map(lectura,0,1023,0,100);
  regreso += porcentaje;
  regreso += ",";
  lectura = analogRead(A2);
  porcentaje = map(lectura,0,1023,0,100);
  regreso += porcentaje;
  regreso += "]";
  return regreso;
}

String bomba(){
  //Funcion simple que regresa el estado de la bomba en el pin A0
  String regreso = "\"bomba\":";
  regreso += pump;
  return regreso;
}

void accionarBomba(char comando){
  Serial.println("Bomba");
  if(comando == '1'){
    digitalWrite(A0,HIGH);
  } else {
    digitalWrite(A0,LOW);
  }
}

void invalido(EthernetClient client){
  Serial.println("Invalido");
  client.println("Invalido");
}

void limpiarBuffer(EthernetClient client){
  Serial.println("Limpiar");
  while(client.available()>0){
    client.read();
  }
}
  
  
  
