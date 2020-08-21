#include <WiFi.h>
#include <WebServer.h>
#include "analogWrite.h"
#include "ESPAsyncWebServer.h"

AsyncWebServer server(80); 

//Wifi Config
const char* ssid = "MIT";  // Enter SSID here
//const char* password = " YourPassword";  //Enter Password here

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

//http variables
String up="dont move";
String down="dont move";
String left="dont move";
String right="dont move";
String cw="dont move";
String ccw="dont move";
String stop="move";

void setup(void){
  Serial.begin(115200);         // Start the Serial communication to send messages to the computer
  delay(10);
  Serial.println('\n');

  //connect to your local wi-fi network, Uncomment if the wifi has password or not. 
  WiFi.begin(ssid);
  //WiFi.begin(ssid,password); 

  //check wi-fi is connected to wi-fi network
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected..!");
  Serial.print("Got IP: "); 
  Serial.println(WiFi.localIP());
  String page = getPage();

  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/html", handleRoot().c_str());
  });
    server.on("/UP", HTTP_POST, [](AsyncWebServerRequest *request){
    up="move";
    request->redirect("/");
  });
  server.on("/UP_Client", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/html", handleUp().c_str());
  });
  server.on("/DOWN", HTTP_POST, [](AsyncWebServerRequest *request){
    down="move";
    request->redirect("/");
  });
    server.on("/DOWN_Client", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/html", handleDown().c_str());
  });
  server.on("/LEFT", HTTP_POST, [](AsyncWebServerRequest *request){
    left="move";
    request->redirect("/");
  });
  server.on("/LEFT_Client", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/html", handleLeft().c_str());
  });
  server.on("/RIGHT", HTTP_POST, [](AsyncWebServerRequest *request){
    right="move";
    request->redirect("/");
  });
  server.on("/RIGHT_Client", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/html", handleRight().c_str());
  });
  server.on("/CW", HTTP_POST, [](AsyncWebServerRequest *request){
    cw="move";
    request->redirect("/");
  });
  server.on("/CW_Client", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/html", handleCW().c_str());
  });
  server.on("/CCW", HTTP_POST, [](AsyncWebServerRequest *request){
    ccw="move";
    request->redirect("/");
  });
    server.on("/CCW_Client", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/html", handleCCW().c_str());
  });
  server.on("/STOP", HTTP_POST, [](AsyncWebServerRequest *request){
    stop="dont move";
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
  String input=up;
  up= "dont move"; 
  return input;
}

String handleDown(){
  String input=down;
  down= "dont move"; 
  return input;
}
String handleLeft(){
  String input=left;
  left= "dont move"; 
  return input;
}

String handleRight(){
  String input=right;
  right= "dont move"; 
  return input;
}

String handleCW(){
  String input=cw;
  cw= "dont move"; 
  return input;
}

String handleCCW(){
  String input=ccw;
  ccw= "dont move"; 
  return input;
}

String handleStop(){
  String input=stop;
  stop= "move"; 
  return input;
}