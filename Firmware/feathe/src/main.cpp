#include <Arduino.h>
#include "BluetoothSerial.h"

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

BluetoothSerial SerialBT;

//Motor pin
int motor[]= {12,27,33,15,32,14};

void right(){
    digitalWrite(motor[0],HIGH);
    digitalWrite(motor[2],HIGH);
    digitalWrite(motor[4],HIGH); 
    delay(1000);
  return;
}

void right(){
    digitalWrite(motor[1],HIGH);
    digitalWrite(motor[3],HIGH);
    digitalWrite(motor[5],HIGH); 
    delay(1000);
  return;
}
void forward(){
    digitalWrite(motor[1],HIGH);
    digitalWrite(motor[2],HIGH); 
    delay(1000);
  return;
}

void backward(){
  digitalWrite(motor[0],HIGH);
  digitalWrite(motor[3],HIGH); 
  Serial.println("backward");
  delay(1000);
return;
}

void cw(){
  digitalWrite(motor[0],HIGH);
  digitalWrite(motor[2],HIGH);
  digitalWrite(motor[4],HIGH); 
  delay(1000); 
return;
}

void ccw(){
  digitalWrite(motor[1],HIGH);
  digitalWrite(motor[3],HIGH);
  digitalWrite(motor[5],HIGH);  
  delay(1000);
return;
}

void move(char c){
  switch (c)
  {
    case 'f':
      forward();
      break;
    case 'b':
      backward();
      break;
    case 'rr':
      cw();
      break;
    case 'rl':
      ccw();
      break;
      case 'l':
      left();
      break;
      case 'r':
      right();
      break;
    default:
      break;
    }
  return;
}
void setup() {
  Serial.begin(9600);
  SerialBT.begin("ESP32test"); //Bluetooth device name
  Serial.println("The device started, now you can pair it with bluetooth!");
  for (int i =0; i < sizeof(motor)-1; i++){
    pinMode(motor[i],OUTPUT);
  }
}

void loop() {
  if (SerialBT.available()) {
    char c = SerialBT.read();
    Serial.println(c);
    move(c);
  }
  for (int i =0; i < sizeof(motor)-1; i++){
    digitalWrite(motor[i],LOW);
  }
}