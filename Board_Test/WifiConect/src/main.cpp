#include <Arduino.h>
#include <WiFi.h>

const char* ssid = "MIT";  // Enter SSID here
//const char* password = " YourPassword";  //Enter Password here

void setup() {
  Serial.begin(115200);         // Start the Serial communication to send messages to the computer
  delay(10);
  Serial.println('\n');
  WiFi.begin(ssid);
  //WiFi.begin(ssid,password); 
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected..!");
  Serial.print("Got IP: "); 
  Serial.println(WiFi.localIP());
}

void loop() {
  // put your main code here, to run repeatedly:
}