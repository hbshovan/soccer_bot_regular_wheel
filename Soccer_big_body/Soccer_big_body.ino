#include <SPI.h>  
#include "RF24.h" 

RF24 myRadio (8, 7); 
struct package
{
  int rx=1;
  int ry=1;
};

byte addresses[][6] = {"0"}; 

typedef struct package Package;
Package data;

// Motor PWM connections
int LPWMA = 5;
int LPWMB = 6;
int RPWMA = 9;
int RPWMB = 10;

void setup() {
  Serial.begin(115200);
	pinMode(LPWMA, OUTPUT);
	pinMode(LPWMB, OUTPUT);
	pinMode(RPWMA, OUTPUT);

  pinMode(RPWMB, OUTPUT);

  
	
  myRadio.begin(); 
  myRadio.setChannel(115); 
  myRadio.setPALevel(RF24_PA_MAX);
  myRadio.setDataRate( RF24_250KBPS ) ; 
  myRadio.openReadingPipe(1, addresses[0]);
  myRadio.startListening();
}

void loop() {


  if (myRadio.available()) {
    while (myRadio.available()) {
      myRadio.read(&data, sizeof(data));
    }

    Serial.print("\nRX: "); Serial.print(data.rx);
    Serial.print(" | RY: "); Serial.println(data.ry);

    int pwmX = 0, pwmY = 0;



            if (data.rx > 480 && data.ry < 400){
              analogWrite(LPWMA, 255);
              analogWrite(LPWMB, 0);
              analogWrite(RPWMA, map(data.rx, 900, 480, 0, 255));
              analogWrite(RPWMB, 0);
              Serial.print("RUp ");
              Serial.println(map(data.rx, 900, 480, 0, 255));
            }else if (data.rx < 400 && data.ry < 400){
              analogWrite(LPWMA, map(data.rx, 0, 399, 0, 255));
              analogWrite(LPWMB, 0);
              analogWrite(RPWMA, 255);
              analogWrite(RPWMB, 0);
              Serial.print("LUp ");
              Serial.println(map(data.rx, 0, 399, 0, 255));
            }else if (data.rx > 480 && data.ry > 480){
              analogWrite(LPWMA, 0);
              analogWrite(LPWMB, 255);
              analogWrite(RPWMA, 0);
              analogWrite(RPWMB, map(data.rx, 900, 480, 0, 255));
              Serial.print("RDown ");
              Serial.println(map(data.rx, 900, 480, 0, 255));
            }else if (data.rx < 400 && data.ry > 480){
              analogWrite(LPWMA, 0);
              analogWrite(LPWMB, map(data.rx, 0, 399, 0, 255));
              analogWrite(RPWMA, 0);
              analogWrite(RPWMB, 255);
              Serial.print("LDown ");
              Serial.println(map(data.rx, 0, 399, 0, 255));
            }else if (data.ry > 480) {
                backward(map(data.ry, 480, 900, 0, 255));
            } else if (data.ry < 400) {
                forward(map(data.ry, 0, 399, 255, 0));
            } else if (data.rx > 480) {
                right(map(data.rx, 480, 900, 0, 255));
            } else if (data.rx < 400) {
                left(map(data.rx, 0, 399, 255, 0));
            } else {
                stopMotors();
            }
    
  }else{
    
  }
}


void stopMotors() {
  Serial.println("Stopped");
  analogWrite(LPWMA, 0);
  analogWrite(LPWMB, 0);
  analogWrite(RPWMA, 0);
  analogWrite(RPWMB, 0);
}

void forward(int speed) {
  Serial.print("\F: "); Serial.println(speed);
  analogWrite(LPWMA, speed);
  analogWrite(LPWMB, 0);
  analogWrite(RPWMA, speed);
  analogWrite(RPWMB, 0);
}

void backward(int speed) {
  Serial.print("\B: "); Serial.println(speed);
  analogWrite(LPWMA, 0);
  analogWrite(LPWMB, speed);
  analogWrite(RPWMA, 0);
  analogWrite(RPWMB, speed);
}

void left(int speed) {
  Serial.print("\L: "); Serial.println(speed);
  analogWrite(LPWMA, 0);
  analogWrite(LPWMB, speed);
  analogWrite(RPWMA, speed);
  analogWrite(RPWMB, 0);
}

void right(int speed) {
  Serial.print("\R: "); Serial.println(speed);
  analogWrite(LPWMA, speed);
  analogWrite(LPWMB, 0);
  analogWrite(RPWMA, 0);
  analogWrite(RPWMB, speed);
}