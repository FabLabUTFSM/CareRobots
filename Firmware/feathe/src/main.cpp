#include <Arduino.h>
#include <wifi.h>
#include <ArduinoJson.h>

// WiFi Config
char ssid[] = "MIT";
//char pass[] =; //Uncomment to set the network password
int status = WL_IDLE_STATUS;

//Json parameters
const size_t capacity = JSON_ARRAY_SIZE(3) + JSON_OBJECT_SIZE(2) + 30;
StaticJsonBuffer<capacity> jsonBuffer;


 
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
      delay(10000);
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
  delay(1000);
  //Serial.println("Holi!");
}