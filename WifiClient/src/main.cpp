#include <Arduino.h>
#include <WiFi.h>
#include <HTTPClient.h>

const char* ssid = "MIT";
//const char* password = "123456789";

const char* serverName = "http://18.21.76.110/";

void setup() {
WiFi.begin(ssid);
while(WiFi.status() != WL_CONNECTED) { 
    delay(500);
    Serial.print(".");
}
Serial.println("");
Serial.print("Connected to WiFi network with IP Address: ");
Serial.println(WiFi.localIP());
}

}

void loop() {
  String httpGETRequest(serverName) {
  HTTPClient http;

  http.begin(serverName);
  char httpResponseCode = http.GET();
  if (httpResponseCode>0) {
    Serial.print("HTTP Response code: ");
    Serial.println(httpResponseCode);
    payload = http.getString();
  }
}