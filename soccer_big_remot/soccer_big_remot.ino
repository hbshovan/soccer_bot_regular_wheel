#include <SPI.h>  
#include "RF24.h"

RF24 myRadio (8, 7);
byte addresses[][6] = {"0"};

struct package
{
  int rx=1;
  int ry=1;
};


typedef struct package Package;
Package data;

const int RX_PIN = A3;
const int RY_PIN = A4;

void setup()
{
  pinMode(RX_PIN, INPUT);
  pinMode(RY_PIN, INPUT);
  delay(1000);
  myRadio.begin();  
  myRadio.setChannel(115); 
  myRadio.setPALevel(RF24_PA_MAX);
  myRadio.setDataRate( RF24_250KBPS ) ; 
  myRadio.openWritingPipe( addresses[0]);
  delay(1000);
}

void loop()
{
  data.rx = analogRead(RX_PIN);
  data.ry = analogRead(RY_PIN);
  myRadio.write(&data, sizeof(data)); 
}