/*******CONECTIONS: Modify the next 2 lines to define the pins your are going to use. 
 * Dont modifiy nothing of you are using the same conections presented in the Fritzing 
 * image. */


const int pinMotor[]= {12,27,15,33,22,23};// {moto1CW,motor1CCW,moto2CW,motor2CCW,moto3CW,motor3CCW}
const int pinEnable[]={13,32,14};

const int motorSpeed = 255; //Motor speed, this variable will define the motor speed, to define the number follow the following ecuation: Max_RPM*motorSpeed/255=Speed_expected. 


/*****************MOTOR DIRECTION**********/
bool motor1 = false;
bool motor2 = true;
bool motor3 = true;

/*******************TORQUE RAMP CONFIGURATION*********/
/**Key:
 * maxPayload: PWM payload in wich the robot breaks the inertia. 
 * minPayload: PWM payload for the normal speed we want to aim for our robot. 
 * torqueRampSmoother: Will set te amount of cycles in wich the robot will reach the desired speed. A big number will take more time to reach the speed, but in a smoother way. 
 * delay: Time wich a PWM torque stays working. 
 The ramp time will be defines by the following equation: (maxPayload-minPayload)*delay/toqueRampSmoother. 
*************************************************************************************************/

bool inMove = false;
const int maxPayload = 255;
const int minPayload = 120;
const int torqueRampSmoother =10; //The smaller this number is, the slower the acceleration will be. 
const int torqueRampDelay= 10;  

/****************** libraries*************/
#include "analogWrite.h"
#include <Arduino.h>

void moveMotor(int motor, String direction); 
void forward();
void left();
void right();
void left();
void down();
void CCW();
void CW();
void stop();
void torqueRamp(String motor1Status, String motor2Status, String motor3Status);

void setup() {
  for (byte i=0; i< sizeof(pinMotor); i++ ){
    pinMode(pinMotor[i],OUTPUT);
  }
  for (byte i=0; i< sizeof(pinEnable); i++ ){
    pinMode(pinEnable[i],OUTPUT);
  }
  Serial.begin(115200);         // Start the Serial communication to send messages to the computer 
}

void loop() {
  CCW();
  delay(1000);
  CW();
  delay(1000);
}

//Standar functions for bluetooth and WiFi
void forward(){
  moveMotor(1,"CCW");
  moveMotor(2,"CW");
  moveMotor(3,"Off");
  torqueRamp("CCW","CW","Off");
}

void left(){
  moveMotor(1,"CCW");
  moveMotor(2,"CCW");
  moveMotor(3,"CW");
  torqueRamp("CCW","CCW","CW");
}

void right(){
  moveMotor(1,"CW");
  moveMotor(2,"CW");
  moveMotor(3,"CCW");
  torqueRamp("CW","CW","CCW");
}

void down(){
  moveMotor(1,"CW");
  moveMotor(2,"CCW");
  moveMotor(3,"Off");
  torqueRamp("CW","CCW","Off");
}

void stop(){
  moveMotor(1,"Off");
  moveMotor(2,"Off");
  moveMotor(3,"Off");
  inMove=false;
}

void CW(){
  moveMotor(1,"CW");
  moveMotor(2,"CW");
  moveMotor(3,"CW");
  torqueRamp("CW","CW","CW");
}

void CCW(){
  moveMotor(1,"CCW");
  moveMotor(2,"CCW");
  moveMotor(3,"CCW");
  torqueRamp("CCW","CCW","CCW");
}


void moveMotor(int motor, String direction){
  switch (motor){
    case 1:
     analogWrite(pinEnable[0],motorSpeed);
      if(direction == "CCW"){
        if (motor1){
          digitalWrite(pinMotor[0],LOW);
          digitalWrite(pinMotor[1],HIGH);
        }
        else
        {
          digitalWrite(pinMotor[0],HIGH);
          digitalWrite(pinMotor[1],LOW);
        }
        
        Serial.print("Motor1: ");
        Serial.println("CCW");
      }
      else if (direction=="CW")
      {
        if (motor1){
          digitalWrite(pinMotor[0],HIGH);
          digitalWrite(pinMotor[1],LOW);
        }
        else
        {
          digitalWrite(pinMotor[0],LOW);
          digitalWrite(pinMotor[1],HIGH);
        }
        Serial.print("Motor1: ");
        Serial.println("CW");
      }
      else 
      {
        digitalWrite(pinEnable[0],LOW);
        digitalWrite(pinMotor[0],LOW);
        digitalWrite(pinMotor[1],LOW);
        Serial.print("Motor1: ");
        Serial.println("Off");
      }
      break;
    case 2: 
      analogWrite(pinEnable[1],motorSpeed);
      if(direction == "CCW"){
        if (motor2){
          digitalWrite(pinMotor[2],LOW);
          digitalWrite(pinMotor[3],HIGH);
        }
        else
        {
          digitalWrite(pinMotor[2],HIGH);
          digitalWrite(pinMotor[3],LOW);
        }
        Serial.print("Motor2: ");
        Serial.println("CCW");
      }
      else if (direction=="CW")
      {
        if (motor2)
        {
          digitalWrite(pinMotor[2],HIGH);
          digitalWrite(pinMotor[3],LOW);
        }
        else
        {
          digitalWrite(pinMotor[2],LOW);
          digitalWrite(pinMotor[3],HIGH);
        }
        
        Serial.print("Motor2: ");
        Serial.println("CW");
      }
      else 
      {   
        digitalWrite(pinEnable[1],LOW);
        digitalWrite(pinMotor[2],LOW);
        digitalWrite(pinMotor[3],LOW);
        Serial.print("Motor2: ");
        Serial.println("Off");
      }
      break;
    case 3:
      analogWrite(pinEnable[2],motorSpeed);
      if(direction == "CCW"){
        if (motor3){
          digitalWrite(pinMotor[4],LOW);
          digitalWrite(pinMotor[5],HIGH);
        }
        else
        {
          digitalWrite(pinMotor[4],HIGH);
          digitalWrite(pinMotor[5],LOW);
        }
        Serial.print("Motor3: ");
        Serial.println("CCW");
      }
      else if (direction=="CW")
      {
        if (motor3)
        {
          digitalWrite(pinMotor[4],HIGH);
          digitalWrite(pinMotor[5],LOW);
        }
        else
        {
          digitalWrite(pinMotor[4],LOW);
          digitalWrite(pinMotor[5],HIGH);
        }
        Serial.print("Motor3: ");
        Serial.println("CW");
      }
      else 
      {
        analogWrite(pinEnable[2],LOW);
        digitalWrite(pinMotor[4],LOW);
        digitalWrite(pinMotor[5],LOW);
        Serial.print("Motor3: ");
        Serial.println("Off");
      }
      break;
  }
}

void torqueRamp(String motor1Status, String motor2Status, String motor3Status){
  int payload = maxPayload;
  int delta = (maxPayload-minPayload)/torqueRampSmoother;
  if(!inMove){
    Serial.println("Torque Ramp");
    while (payload > minPayload)
    {
      if (motor1Status != "Off")
      {
        analogWrite(pinEnable[0],payload);
      }
      if (motor2Status != "Off")
      {
        analogWrite(pinEnable[1],payload);
      }
      if (motor3Status != "Off")
      {
        analogWrite(pinEnable[3],payload);
      }
      payload=payload-delta;
      delay(500);
    }
    inMove= true;
  }
}