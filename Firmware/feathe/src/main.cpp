#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WiFiMulti.h> 
#include <ESP8266mDNS.h>
#include <ESP8266WebServer.h>   // Include the WebServer library

ESP8266WiFiMulti wifiMulti;     // Create an instance of the ESP8266WiFiMulti class, called 'wifiMulti'

ESP8266WebServer server(80);    // Create a webserver object that listens for HTTP request on port 80

const int motor[]= {12,27,33,15,32,14};

/// Create the website


String getPage(){
  //String page = "<html lang=fr-FR><head><meta http-equiv='refresh' content='10'/>";
  String page = "<html lang=fr-FR><head>";
  page += "<title>COVID19-CareBOT v1.0</title>";
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
  page += " </table>" ;
  page += "</body></html>";
  return page;
}


void handleRoot();              // function prototypes for HTTP handlers
void handleNotFound();

void handleUP();   ///Adding functions towards MOTORS --> JORDI
void handleLEFT();   ///Adding functions towards MOTORS --> JORDI
void handleRIGHT();   ///Adding functions towards MOTORS --> JORDI
void handleDOWN();   ///Adding functions towards MOTORS --> JORDI
void handleSTOP();   ///Adding functions towards MOTORS --> JORDI

void setup(void){
  for (int i =0; i < sizeof(motor)-1; i++){
    pinMode(motor[i],OUTPUT);
  }
  
  Serial.begin(115200);         // Start the Serial communication to send messages to the computer
  delay(10);
  Serial.println('\n');

  wifiMulti.addAP("Lighthouse19", "4753olga");   // add Wi-Fi networks you want to connect to
  wifiMulti.addAP("ssid_from_AP_2", "your_password_for_AP_2");
  wifiMulti.addAP("ssid_from_AP_3", "your_password_for_AP_3");

  Serial.println("Connecting ...");
  int i = 0;
  while (wifiMulti.run() != WL_CONNECTED) { // Wait for the Wi-Fi to connect: scan for Wi-Fi networks, and connect to the strongest of the networks above
    delay(250);
    Serial.print('.');
  }
  Serial.println('\n');
  Serial.print("Connected to ");
  Serial.println(WiFi.SSID());              // Tell us what network we're connected to
  Serial.print("IP address:\t");
  Serial.println(WiFi.localIP());           // Send the IP address of the ESP8266 to the computer

  if (MDNS.begin("esp8266")) {              // Start the mDNS responder for esp8266.local
    Serial.println("mDNS responder started");
  } else {
    Serial.println("Error setting up MDNS responder!");
  }

  server.on("/", HTTP_GET, handleRoot);     // Call the 'handleRoot' function when a client requests URI "/"
  server.on("/UP", HTTP_POST, handleUP);  // Call the 'handleLED' function when a POST request is made to URI "/UP"
  server.on("/LEFT", HTTP_POST, handleLEFT);  // Call the 'handleLED' function when a POST request is made to URI "/LEFT"
  server.on("/RIGHT", HTTP_POST, handleRIGHT);  // Call the 'handleLED' function when a POST request is made to URI "/RIGHT"
  server.on("/DOWN", HTTP_POST, handleDOWN);  // Call the 'handleLED' function when a POST request is made to URI "/DOWN"
  server.on("/STOP", HTTP_POST, handleSTOP);  // Call the 'handleLED' function when a POST request is made to URI "/DOWN"
 
  
  server.onNotFound(handleNotFound);        // When a client requests an unknown URI (i.e. something other than "/"), call function "handleNotFound"

  server.begin();                           // Actually start the server
  Serial.println("HTTP server started");
}

void loop(void){
  server.();                    // Listen for HTTP requests from clients
}

void handleRoot() {                         // When URI / is requested, send a web page with a button to toggle the LED
  server.send(200, "text/html", getPage());
}

void handleUP() {                          // If a POST request is made to URI /LED
    digitalWrite(motor[1],HIGH);
    digitalWrite(motor[2],HIGH);
    digitalWrite(motor[3],LOW);
    digitalWrite(motor[4],LOW);
    digitalWrite(motor[5],LOW);
    digitalWrite(motor[0],LOW);
  server.sendHeader("Location","/");        // Add a header to respond with a new location for the browser to go to the home page again
  server.send(303);                         // Send it back to the browser with an HTTP status 303 (See Other) to redirect
}

void handleLEFT() {                          // If a POST request is made to URI /LED
    digitalWrite(motor[0],HIGH);
    digitalWrite(motor[2],HIGH);
    digitalWrite(motor[4],HIGH); 
    digitalWrite(motor[1],LOW);
    digitalWrite(motor[3],LOW);
    digitalWrite(motor[5],LOW); 
  server.sendHeader("Location","/");        // Add a header to respond with a new location for the browser to go to the home page again
  server.send(303);                         // Send it back to the browser with an HTTP status 303 (See Other) to redirect
}
void handleRIGHT() {                          // If a POST request is made to URI /LED
  digitalWrite(motor[1],HIGH);
  digitalWrite(motor[3],HIGH);
  digitalWrite(motor[5],HIGH); 
  digitalWrite(motor[0],LOW);
  digitalWrite(motor[2],LOW);
  digitalWrite(motor[4],LOW);
  server.sendHeader("Location","/");        // Add a header to respond with a new location for the browser to go to the home page again
  server.send(303);                         // Send it back to the browser with an HTTP status 303 (See Other) to redirect
}
void handleDOWN() {                          // If a POST request is made to URI /LED
  digitalWrite(motor[0],HIGH);
  digitalWrite(motor[3],HIGH); 
  digitalWrite(motor[0],LOW);
  digitalWrite(motor[3],LOW); 
  digitalWrite(motor[0],LOW);
  digitalWrite(motor[3],LOW); 
  server.sendHeader("Location","/");        // Add a header to respond with a new location for the browser to go to the home page again
  server.send(303);                         // Send it back to the browser with an HTTP status 303 (See Other) to redirect
}


void handleSTOP() {                          // If a POST request is made to URI /LED
  digitalWrite(LF,LOW);      // Change the state of the LED
  digitalWrite(LB,LOW);      // Change the state of the LED
  digitalWrite(ENL,LOW);      // Change the state of the LED
  digitalWrite(RF,LOW);      // Change the state of the LED
  digitalWrite(RB,LOW);      // Change the state of the LED
  digitalWrite(ENR,LOW);      // Change the state of the LED
  server.sendHeader("Location","/");        // Add a header to respond with a new location for the browser to go to the home page again
  server.send(303);                         // Send it back to the browser with an HTTP status 303 (See Other) to redirect
}




void handleNotFound(){
  server.send(404, "text/plain", "404: Not found"); // Send HTTP status 404 (Not Found) when there's no handler for the URI in the request
}