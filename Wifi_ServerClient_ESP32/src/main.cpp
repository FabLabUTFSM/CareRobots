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
const int pinEnable[]={21,32,14};

const int motorSpeed = 220; //Motor speed, this variable will define the motor speed, to define the number follow the following ecuation: Max_RPM*motorSpeed/255=Speed_expected. 

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

/*****************MOTOR DIRECTION**********/
bool motor1 = false;
bool motor2 = true;
bool motor3 = true;

/******DON NOT MODIFY PASS HERE*********/

#include <WiFi.h>
#include <WebServer.h>
#include "analogWrite.h"
#include "ESPAsyncWebServer.h"

const int led = 13;

AsyncWebServer server(80); 

/// Create the website
String getPage(){
  //String page = "<html lang=fr-FR><head><meta http-equiv='refresh' content='10'/>";
  String page = "<html lang=fr-FR><head>";
  page += "<title>COVID19-CareROBOT v1.0</title>";
  page += "<style> body { background-color: #fffff; font-family: Arial, Helvetica, Sans-Serif; Color: #000088; }</style>";
  page += "</head><body><h1>COVID19-CareBOT v1.0</h1>";
  page += "<table>";
  page += " <tr> ";
  page += "   <th></th> ";
  page += "   <th><form action=\"/UP\" method=\"POST\"><input type=\"submit\" value=\"&#x2B06;\"></form></th>";
  page += "   <th></th>" ;
  page += " </tr>" ;
  page += " <tr>" ;
  page += "  <td><form action=\"/LEFT\" method=\"POST\"><input type=\"submit\" value=\"&#x2B05;\"></form></td>" ;
  page += "   <td><form action=\"/STOP\" method=\"POST\"><input type=\"submit\" value=\"&#x25FC;\"></form></td>" ;
  page += "   <td><form action=\"/RIGHT\" method=\"POST\"><input type=\"submit\" value=\"&#x27A1;\"></form></td>" ;
  page += " </tr>" ;
  page += " <tr>" ;
  page += "   <td></td>" ;
  page += "   <td><form action=\"/DOWN\" method=\"POST\"><input type=\"submit\" value=\"&#x2B07;\"></form></td>" ;
  page += "   <td></td>" ;
  page += " </tr>" ;
  page += " <tr>" ;
  page += "   <td></td>" ;
  page += "   <td><form action=\"/CW\" method=\"POST\"><input type=\"submit\" value=\"&#x21BB;\"></form></td>" ;
  page += "   <td><form action=\"/CCW\" method=\"POST\"><input type=\"submit\" value=\"&#x21ba;\"></form></td>";
  page += "   <td></td>" ;         
  page += " </tr>" ;
  page += " </table>" ;
  page += "</body></html>";
  return page;
}


//Function declaration

String handleRoot();
String handleUp();
String handleDown();
String handleLeft();
String handleRight();
String handleCW();
String handleCCW();
String handleStop();
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

//http variables
String up_send="dont move";
String down_send="dont move";
String left_send="dont move";
String right_send="dont move";
String cw_send="dont move";
String ccw_send="dont move";
String stop_send="move";

void setup(void){
  pinMode(led,OUTPUT);
  digitalWrite(led,LOW);
  for (byte i=0; i< sizeof(pinMotor); i++ ){
    pinMode(pinMotor[i],OUTPUT);
    digitalWrite(pinMotor[i],LOW);
  }
  for (byte i=0; i< sizeof(pinEnable); i++ ){
    pinMode(pinEnable[i],OUTPUT);
    digitalWrite(pinMotor[i],LOW);
  }
  Serial.begin(115200);         // Start the Serial communication to send messages to the computer
  delay(10);
  Serial.println('\n');

  //connect to your local wi-fi network, Uncomment if the wifi has password or not. 
  if (wifiPass){
    WiFi.begin(ssid,password);
  }
  else
  {
    WiFi.begin(ssid);
  } 

  //check wi-fi is connected to wi-fi network
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  digitalWrite(led,HIGH);
  Serial.println("");
  Serial.println("WiFi connected..!");
  Serial.print("Got IP: "); 
  Serial.println(WiFi.localIP());
  String page = getPage();

  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/html", handleRoot().c_str());
  });
    server.on("/UP", HTTP_POST, [](AsyncWebServerRequest *request){
    up_send="move";
    forward();
    Serial.println("forward"); 
    request->redirect("/");
  });
  server.on("/UP_Client", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/html", handleUp().c_str());
  });
  server.on("/DOWN", HTTP_POST, [](AsyncWebServerRequest *request){
    down_send="move";
    down();
    Serial.println("down"); 
    request->redirect("/");
  });
    server.on("/DOWN_Client", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/html", handleDown().c_str());
  });
  server.on("/LEFT", HTTP_POST, [](AsyncWebServerRequest *request){
    left_send="move";
    left();
    Serial.println("left");
    request->redirect("/");
  });
  server.on("/LEFT_Client", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/html", handleLeft().c_str());
  });
  server.on("/RIGHT", HTTP_POST, [](AsyncWebServerRequest *request){
    right_send="move";
    right();
    Serial.println("right");
    request->redirect("/");
  });
  server.on("/RIGHT_Client", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/html", handleRight().c_str());
  });
  server.on("/CW", HTTP_POST, [](AsyncWebServerRequest *request){
    cw_send="move";
    CW();
    Serial.println("CW");
    request->redirect("/");
  });
  server.on("/CW_Client", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/html", handleCW().c_str());
  });
  server.on("/CCW", HTTP_POST, [](AsyncWebServerRequest *request){
    ccw_send="move";
    CCW();
    Serial.println("CCW");
    request->redirect("/");
  });
    server.on("/CCW_Client", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/html", handleCCW().c_str());
  });
  server.on("/STOP", HTTP_POST, [](AsyncWebServerRequest *request){
    stop_send="dont move";
    stop();
    Serial.println("stop");
    request->redirect("/");
  });
    server.on("/STOP_Client", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/html", handleStop().c_str());
  });

  server.begin();                           // Actually start the server
  Serial.println("HTTP server started");

}

void loop(){
    
}

String handleRoot() {
  return getPage();
}

String handleUp(){
  String input=up_send;
  up_send= "dont move";
  return input;
}

String handleDown(){
  String input=down_send;
  down_send= "dont move"; 
  return input;
}
String handleLeft(){
  String input=left_send;
  left_send= "dont move"; 
  return input;
}

String handleRight(){
  String input=right_send;
  right_send= "dont move"; 
  return input;
}

String handleCW(){
  String input=cw_send;
  cw_send= "dont move"; 
  return input;
}

String handleCCW(){
  String input=ccw_send;
  ccw_send= "dont move"; 
  return input;
}

String handleStop(){
  String input=stop_send;
  stop_send= "move"; 
  return input;
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