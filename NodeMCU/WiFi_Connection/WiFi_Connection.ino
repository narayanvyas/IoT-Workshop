/* NodeMCU WiFi Connection

   GitHub URL - https://github.com/narayanvyas/IoT-workshop

   Components
   ----------
    - NodeMCU

*/

#include <ESP8266WiFi.h>    // Header File for ESP8266 NodeMCU

/* Set these to your desired credentials. */
const char *ssid = "Redmi"; //Declare pointer for ssid as constant 
const char *password = "123456789";//Declare pointer for password as constant

void setup() {
  Serial.begin(9600); //start the Serial monitor with 9600 of baud rate. 
  pinMode(LED_BUILTIN, OUTPUT); //declare pinMode for LED
  digitalWrite(LED_BUILTIN, LOW);//Setting LED off.

  //Trying to connect to the WiFi

  Serial.println("Connecting to WiFi");
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    digitalWrite(LED_BUILTIN, HIGH);
    delay(500);
    Serial.print("*");
    digitalWrite(LED_BUILTIN, LOW);
  }
  
  Serial.println("WiFi Connected");
  Serial.println(WiFi.localIP());   // Printing the IP Address
  digitalWrite(LED_BUILTIN, HIGH);
}

void loop() {
  
}
