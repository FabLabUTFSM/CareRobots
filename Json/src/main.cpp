#include <Arduino.h>
#include <ArduinoJson.h>
#include <WiFi.h>
#include <HTTPClient.h>

const char* ssid = "MIT";  // Enter SSID here
//const char* password = " YourPassword";  //Enter Password here

const char* serverName = "http://arduinojson.org/example.json";

HTTPClient http;
DynamicJsonDocument doc(101);

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
  HTTPClient http;    //Declare object of class HTTPClient  
  http.begin(serverName);     //Specify request destination
  
  int httpCode = http.GET();            //Send the request
  String payload = http.getString();    //Get the response payload from server
  
  if(httpCode == 200)
  {

  
   // Parse JSON object
  deserializeJson(doc, payload);
  
    // Decode JSON/Extract values
  Serial.println(F("Response:"));
  Serial.println(doc["sensor"].as<char*>());
  Serial.println(doc["time"].as<long>());
  Serial.println(doc["data"][0].as<float>(), 6);
  Serial.println(doc["data"][1].as<float>(), 6);
  }
  else
  {
    Serial.println("Error in response");
  }
 
  http.end();  //Close connection
  
  delay(5000);  //GET Data at every 5 seconds
}