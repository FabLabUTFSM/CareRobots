#include <Arduino.h>
#include <wifi.h>
#include <ArduinoJson.h>// v6 library
#include<HTTPClient.h>

// WiFi Config
char ssid[] = "MIT";
//char pass[] =; //Uncomment to set the network password
int status = WL_IDLE_STATUS;
bool conection;
WiFiClient client;
char server[]= "http://arduinojson.org/example.json"; //website where json comes

//Json parameters
//const size_t capacity = JSON_ARRAY_SIZE(3) + JSON_OBJECT_SIZE(2) + 30; //json format {"direction": String, "speed":[int motor1, int motor2, int motor3]}
const size_t capacity = JSON_ARRAY_SIZE(2) + JSON_OBJECT_SIZE(3) + 30; //json test
StaticJsonDocument<capacity> doc;

void getjson(){
  HTTPClient http;
  http.begin("http://arduinojson.org/example.json");
  http.GET();
  doc.clear();
  deserializeJson(doc, http.getStream());
  http.end();  
}

 
void setup() {
  //Serial setup
  Serial.begin(9600);
  //WiFi setup
  WiFi.begin(ssid); //Uncomment if the wifi network doesn't have a password
  //WiFi.begin(ssid,pass); //Uncomment if the wifi network has a password
  while ( status != WL_CONNECTED) {
      Serial.print("Attempting to connect to WEP network, SSID: ");
      Serial.println(ssid);
      status = WiFi.begin(ssid);

      // wait 10 seconds for connection:
      delay(1000);
  }
  if (status== WL_CONNECT_FAILED){
    Serial.println("Unable to connect to WiFi");
  }
  else
  {
    Serial.print("Conected to: ");
    Serial.println(ssid);
  }
}

void loop() {
  getjson();
  Serial.println(doc["time"].as<long>());
}