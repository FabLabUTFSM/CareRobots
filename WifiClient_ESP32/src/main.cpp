#include <Arduino.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include "analogWrite.h"

const char* ssid = "MIT";
//const char* password = "lololo111";


const char* serverNameUp = "http://10.31.234.247/UP_Client";
const char* serverNameDown = "http://10.31.234.247/DOWN_Client";
const char* serverNameLeft = "http://10.31.234.247/LEFT_Client";
const char* serverNameRight = "http://10.31.234.247/RIGHT_Client";
const char* serverNameCW = "http://10.31.234.247/CW_Client";
const char* serverNameCCW = "http://10.31.234.247/CCW_Client";
const char* serverNameStop = "http://10.31.234.247/STOP_Client";


String httpGETRequest(const char* server);
void moveMotor(int motor, String direction);  /// Function that makes the motor rotate CW or CCW --> Joseto
void forward();
void left();
void right();
void left();
void down();
void CCW();
void CW();
void scan();
void stop();

const int pinMotor[]= {12,27,15,33,22,23};// {moto1CW,motor1CCW,moto2CW,motor2CCW,moto3CW,motor3CCW}
//const int pinMotor[]= {11,12,13,14,16,17};

const int pinEnable[]={13,32,14};
//const int pinEnable[]={10,15,18};

const int motorSpeed = 255;

void setup() {
for (byte i=0; i< sizeof(pinMotor); i++ ){
  pinMode(pinMotor[i],OUTPUT);
}
for (byte i=0; i< sizeof(pinEnable); i++ ){
  pinMode(pinEnable[i],OUTPUT);
}
Serial.begin(115200);
//WiFi.begin(ssid,password);
WiFi.begin(ssid);
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
    
  // Your IP address with path or Domain name with URL path 
  http.begin(server);
  
  // Send HTTP POST request
  int httpResponseCode = http.GET();
  
  String payload = "--"; 
  
  if (httpResponseCode>0) {
    //Serial.println(httpResponseCode);
    payload = http.getString();
  }
  else {
  }
  // Free resources
  http.end();

  return payload;
}
//Standar functions for bluetooth and WiFi
void forward(){
  moveMotor(1,"CCW");
  moveMotor(2,"CW");
  moveMotor(3,"Off");
  delay(100);
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
     digitalWrite(pinEnable[0],HIGH);
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
        digitalWrite(pinEnable[0],LOW);
        digitalWrite(pinMotor[0],LOW);
        digitalWrite(pinMotor[1],LOW);
        Serial.print("Motor1: ");
        Serial.println("Off");
      }
      break;
    case 2: 
      digitalWrite(pinEnable[1],HIGH);
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
        analogWrite(pinEnable[2],LOW);
        digitalWrite(pinMotor[4],LOW);
        digitalWrite(pinMotor[5],LOW);
        Serial.print("Motor3: ");
        Serial.println("Off");
      }
      break;
  }

}