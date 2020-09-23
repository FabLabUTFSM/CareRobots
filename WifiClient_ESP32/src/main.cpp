/***********CONFIGURATION************
 * This section will define all the variables the user is spected to
 * configurate, please don't modify the other sections*/

bool wifiPass = false; //True if the WiFi network has password; False if not. 
const char* ssid = "MIT"; //WiFi ssid
const char* password = ""; //WiFi password

/*******CONECTIONS: Modify the next 2 lines to define the pins your are going to use. 
 * Dont modifiy nothing of you are using the same conections presented in the Fritzing 
 * image. */

const int pinMotor[]= {12,27,15,33,22,23};// {moto1CW,motor1CCW,moto2CW,motor2CCW,moto3CW,motor3CCW}
const int pinEnable[]={13,32,14};

const int motorSpeed = 255; //Motor speed, this variable will define the motor speed, to define the number follow the following ecuation: Max_RPM*motorSpeed/255=Speed_expected. 

/*******************TORQUE RAMP CONFIGURATIO*********/
/**Key:
 * maxPayload: PWM payload in wich the robot breaks the inertia. 
 * minPayload: PWM payload for the normal speed we want to aim for our robot. 
 * torqueRampSmoother: Will set te amount of cycles in wich the robot will reach the desired speed. A big number will take more time to reach the speed, but in a smoother way. 
*************************************************************************************************/

bool inMove = false;
const int maxPayload = 255;
const int minPayload = 120;
const int torqueRampSmoother =10; //The smaller this number is, the slower the acceleration will be. 

/*****************MOTOR DIRECTION**********/
bool motor1 = false;
bool motor2 = true;
bool motor3 = true;

/******DON NOT MODIFY PASS HERE*********/

#include <Arduino.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include "analogWrite.h"

const char* serverNameUp = "http://10.31.234.247/UP_Client";
const char* serverNameDown = "http://10.31.234.247/DOWN_Client";
const char* serverNameLeft = "http://10.31.234.247/LEFT_Client";
const char* serverNameRight = "http://10.31.234.247/RIGHT_Client";
const char* serverNameCW = "http://10.31.234.247/CW_Client";
const char* serverNameCCW = "http://10.31.234.247/CCW_Client";
const char* serverNameStop = "http://10.31.234.247/STOP_Client";

String httpGETRequest(const char* server);
void moveMotor(int motor, String direction); 
void forward();
void left();
void right();
void left();
void down();
void CCW();
void CW();
void scan();
void stop();
void torqueRamp();


void setup() {
for (byte i=0; i< sizeof(pinMotor); i++ ){
  pinMode(pinMotor[i],OUTPUT);
}
for (byte i=0; i< sizeof(pinEnable); i++ ){
  pinMode(pinEnable[i],OUTPUT);
}
Serial.begin(115200);
if (wifiPass){
  WiFi.begin(ssid,password);
}
else
{
WiFi.begin(ssid);
}
while(WiFi.status() != WL_CONNECTED) { 
    delay(500);
    Serial.print(".");
}
Serial.println("");
Serial.print("Connected to WiFi network with IP Address: ");
Serial.println(WiFi.localIP());
moveMotor(1,"Off");
moveMotor(2,"Off");
moveMotor(3,"Off");
}

void loop() {
  scan();
}

void scan(){
  String upStatus = httpGETRequest(serverNameUp);
  if(upStatus=="move"){
    forward();
    Serial.println("forward");
  }
  String downStatus = httpGETRequest(serverNameDown);
  if(downStatus=="move"){
    down();
    Serial.println("down");
  }
  String leftStatus = httpGETRequest(serverNameLeft);
  if(leftStatus=="move"){
    left();
    Serial.println("left");
  }
  String rightStatus = httpGETRequest(serverNameRight);
  if(rightStatus=="move"){
    right();
    Serial.println("right");
  }
  String cwStatus = httpGETRequest(serverNameCW);
  if(cwStatus=="move"){
    CW();
    Serial.println("cw");
  }
  String ccwStatus = httpGETRequest(serverNameCCW);
  if(ccwStatus=="move"){
    CCW();
    Serial.println("ccw");
  }
  String stopStatus = httpGETRequest(serverNameStop);
  if(stopStatus=="dont move"){
    stop();
    Serial.println("stop");
  }
}

String httpGETRequest(const char* server) {
  HTTPClient http;
  http.begin(server);
  int httpResponseCode = http.GET();
  String payload = "--"; 
  if (httpResponseCode>0) {
    payload = http.getString();
  }
  else {
  }
  http.end();

  return payload;
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