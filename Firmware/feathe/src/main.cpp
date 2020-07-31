#include <Arduino.h>
#include <wifi.h>

// WiFi Config
char ssid[] = "MIT";
//char pass[] =; //Uncomment to set the network password
int status = WL_IDLE_STATUS;
 
void setup() {
  Serial.begin(9600);
  //Serial.println("Holi!");
  WiFi.begin(ssid); //Uncomment if the wifi network doesn't have a password
  //WiFi.begin(ssid,pass); //Uncomment if the wifi network has a password
  while ( status != WL_CONNECTED) {
      Serial.print("Attempting to connect to WEP network, SSID: ");
      Serial.println(ssid);
      status = WiFi.begin(ssid);

      // wait 10 seconds for connection:
      delay(10000);
  }
  Serial.print("Conected to: ");
  Serial.println(ssid);
}

void loop() {
  delay(1000);
  //Serial.println("Holi!");
}