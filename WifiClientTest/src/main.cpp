#include <Arduino.h>
#include <WiFi.h>
#include <HTTPClient.h>


const char* ssid = "MIT";
//const char* password = "lololo111";

const char* serverName = "http://18.21.85.70/UP_Client";



String httpGETRequest(const char* server);

void setup() {
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
}

void loop() {
  Serial.println(httpGETRequest(serverName));
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