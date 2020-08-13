#include <Arduino.h>
#include "BluetoothSerial.h"

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

BluetoothSerial SerialBT;

//Motor pin
int pinMotor[]= {12,27,33,15,32,14}; // {moto1CW,motor1CCW,moto2CW,motor2CCW,moto3CW,motor3CCW}

//const char* input[] = "aefibdc"; // char that the board gets from the BT app, in order: forward, down, cw, ccw, left, right, stop

void BT();
void move(char c);
void forward();
void left();
void right();
void down();
void stop();
void moveMotor(int motor, String direction);


void setup() {
  Serial.begin(9600);
  SerialBT.begin("ESP32test"); //Bluetooth device name
  Serial.println("The device started, now you can pair it with bluetooth!");
  for (int i =0; i < sizeof(pinMotor)-1; i++){
    pinMode(pinMotor[i],OUTPUT);
  }
}

void loop() {
  BT();
}

void BT(){
  if (SerialBT.available()){
    char c = SerialBT.read();
    move(c);
  }
}

void move(char c){
  switch (c)
  {
    case 'a':
      forward();
      break;
    case 'e':
      down();
      break;
    /*case 'f':
      cw();
      break;
    case 'i':
      ccw();
      break;*/
    case 'b':
      left();
      break;
    case 'd':
      right();
      break;
    case 'c':
      stop();
      break;
    default:
      break;
    }
  return;
}

//Standar functions for bluetooth and WiFi
void forward(){
  moveMotor(1,"CCW");
  moveMotor(2,"CW");
  moveMotor(3,"Off");
}

void left(){
  moveMotor(1,"CCW");
  moveMotor(2,"CCW");
  moveMotor(3,"CW");
}

void right(){
  moveMotor(1,"CW");
  moveMotor(2,"CW");
  moveMotor(3,"CCW");
}

void down(){
  moveMotor(1,"CW");
  moveMotor(2,"CCW");
  moveMotor(3,"Off");
}

void stop(){
  moveMotor(1,"Off");
  moveMotor(2,"Off");
  moveMotor(3,"Off");
}

void CW(){
  moveMotor(1,"CW");
  moveMotor(2,"CW");
  moveMotor(3,"CW");
}

void CCW(){
  moveMotor(1,"CCW");
  moveMotor(2,"CCW");
  moveMotor(3,"CCW");
}

void moveMotor(int motor, String direction){
  switch (motor){
    case 1:
      if(direction == "CCW"){
        digitalWrite(pinMotor[0],LOW);
        digitalWrite(pinMotor[1],HIGH);
        Serial.print("Motor1: ");
        Serial.println("CCW");
      }
      else if (direction=="CW")
      {
        digitalWrite(pinMotor[0],HIGH);
        digitalWrite(pinMotor[1],LOW);
        Serial.print("Motor1: ");
        Serial.println("CW");
      }
      else 
      {
        digitalWrite(pinMotor[0],LOW);
        digitalWrite(pinMotor[1],LOW);
        Serial.print("Motor1: ");
        Serial.println("Off");
      }
      break;
    case 2: 
      if(direction == "CCW"){
        digitalWrite(pinMotor[2],LOW);
        digitalWrite(pinMotor[3],HIGH);
        Serial.print("Motor2: ");
        Serial.println("CCW");
      }
      else if (direction=="CW")
      {
        digitalWrite(pinMotor[2],HIGH);
        digitalWrite(pinMotor[3],LOW);
        Serial.print("Motor2: ");
        Serial.println("CW");
      }
      else 
      {
        digitalWrite(pinMotor[2],LOW);
        digitalWrite(pinMotor[3],LOW);
        Serial.print("Motor1: ");
        Serial.println("Off");
      }
      break;
    case 3:
      if(direction == "CCW"){
        digitalWrite(pinMotor[4],LOW);
        digitalWrite(pinMotor[5],HIGH);
        Serial.print("Motor3: ");
        Serial.println("CCW");
      }
      else if (direction=="CW")
      {
        digitalWrite(pinMotor[4],HIGH);
        digitalWrite(pinMotor[5],LOW);
        Serial.print("Motor3: ");
        Serial.println("CW");
      }
      else 
      {
        digitalWrite(pinMotor[4],LOW);
        digitalWrite(pinMotor[5],LOW);
        Serial.print("Motor1: ");
        Serial.println("Off");
      }
      break;
  }

}