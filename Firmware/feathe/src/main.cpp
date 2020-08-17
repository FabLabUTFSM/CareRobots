#include <WiFi.h>
#include <WebServer.h>

WebServer server(80);    // Create a webserver object that listens for HTTP request on port 80

const int pinMotor[]= {32,33,25,26,12,13};// {moto1CW,motor1CCW,moto2CW,motor2CCW,moto3CW,motor3CCW}
//const int pinMotor[]= {12,13,14,15,18,19};

const int pinEnable[]={35,27,14};
//const int pinEnable[]={11,16,17};


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

void moveMotor(int motor, String direction);  /// Function that makes the motor rotate CW or CCW --> Joseto
void handleRoot();              // function prototypes for HTTP handlers
void handleNotFound();
void handleUP();   ///Adding functions towards MOTORS --> JORDI
void handleLEFT();   ///Adding functions towards MOTORS --> JORDI
void handleRIGHT();   ///Adding functions towards MOTORS --> JORDI
void handleDOWN();   ///Adding functions towards MOTORS --> JORDI
void handleSTOP();   ///Adding functions towards MOTORS --> JORDI
void handleCW(); ///Adding function rotate CW --> Joseto
void handleCCW(); ///Adding function rotate CCW --> Joseto

void setup(void){
  for (int i =0; i < sizeof(pinMotor)-1; i++){
    pinMode(pinMotor[i],OUTPUT);
  }
  
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

  server.on("/", HTTP_GET, handleRoot);     // Call the 'handleRoot' function when a client requests URI "/"
  server.on("/UP", HTTP_POST, handleUP);  // Call the 'handleLED' function when a POST request is made to URI "/UP"
  server.on("/LEFT", HTTP_POST, handleLEFT);  // Call the 'handleLED' function when a POST request is made to URI "/LEFT"
  server.on("/RIGHT", HTTP_POST, handleRIGHT);  // Call the 'handleLED' function when a POST request is made to URI "/RIGHT"
  server.on("/DOWN", HTTP_POST, handleDOWN);  // Call the 'handleLED' function when a POST request is made to URI "/DOWN"
  server.on("/STOP", HTTP_POST, handleSTOP);  // Call the 'handleLED' function when a POST request is made to URI "/DOWN"
  server.on("/CW", HTTP_POST, handleCW);  // Call the 'handleLED' function when a POST request is made to URI "/DOWN"
  server.on("/CCW", HTTP_POST, handleCCW);  // Call the 'handleLED' function when a POST request is made to URI "/DOWN"
 
  
  server.onNotFound(handleNotFound);        // When a client requests an unknown URI (i.e. something other than "/"), call function "handleNotFound"

  server.begin();                           // Actually start the server
  Serial.println("HTTP server started");
}

void loop(void){
  server.handleClient();                  // Listen for HTTP requests from clients
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
        Serial.print("Motor1: ");
        Serial.println("Off");
      }
      break;
    case 3:
      digitalWrite(pinEnable[2],HIGH);
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
        digitalWrite(pinEnable[1],LOW);
        digitalWrite(pinMotor[4],LOW);
        digitalWrite(pinMotor[5],LOW);
        Serial.print("Motor1: ");
        Serial.println("Off");
      }
      break;
  }

}

//Functions fo HTML comunication

void handleRoot() {                         // When URI / is requested, send a web page with a button to toggle the LED
  server.send(200, "text/html", getPage());
}

void handleUP() {                          // If a POST request is made to URI /LED
  forward();
  server.sendHeader("Location","/");        // Add a header to respond with a new location for the browser to go to the home page again
  server.send(303);                         // Send it back to the browser with an HTTP status 303 (See Other) to redirect
}

void handleLEFT() {                          // If a POST request is made to URI /LED
  left();
  server.sendHeader("Location","/");        // Add a header to respond with a new location for the browser to go to the home page again
  server.send(303);                         // Send it back to the browser with an HTTP status 303 (See Other) to redirect
}
void handleRIGHT() {                          // If a POST request is made to URI /LED
  right();
  server.sendHeader("Location","/");        // Add a header to respond with a new location for the browser to go to the home page again
  server.send(303);                         // Send it back to the browser with an HTTP status 303 (See Other) to redirect
}
void handleDOWN() {                          // If a POST request is made to URI /LED
  down();
  server.sendHeader("Location","/");        // Add a header to respond with a new location for the browser to go to the home page again
  server.send(303);                         // Send it back to the browser with an HTTP status 303 (See Other) to redirect
}

void handleSTOP() {                          // If a POST request is made to URI /LED
  stop();
  server.sendHeader("Location","/");        // Add a header to respond with a new location for the browser to go to the home page again
  server.send(303);                         // Send it back to the browser with an HTTP status 303 (See Other) to redirect
}

void handleCW() {                          // If a POST request is made to URI /LED
  CW();
  server.sendHeader("Location","/");        // Add a header to respond with a new location for the browser to go to the home page again
  server.send(303);                         // Send it back to the browser with an HTTP status 303 (See Other) to redirect
}

void handleCCW() {                          // If a POST request is made to URI /LED
  CCW();
  server.sendHeader("Location","/");        // Add a header to respond with a new location for the browser to go to the home page again
  server.send(303);                         // Send it back to the browser with an HTTP status 303 (See Other) to redirect
}

void handleNotFound(){
  server.send(404, "text/plain", "404: Not found"); // Send HTTP status 404 (Not Found) when there's no handler for the URI in the request
}
