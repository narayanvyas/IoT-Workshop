#include <ESP8266WiFi.h>
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"

// the OnOff button feed turns this RELAY on/off
#define myDeviceOne 5  // ESP8266 GPIO5
#define myDeviceTwo 4  // ESP8266 GPIO4

/************************* WiFi Access Point *********************************/

#define WLAN_SSID       "Redmi"
#define WLAN_PASS       "123456789"

/************************* Adafruit.io Setup *********************************/

#define AIO_SERVER      "io.adafruit.com"
#define AIO_SERVERPORT  1883                   // 1883 for http 8883 for https
#define AIO_USERNAME    "narayanvyas"
#define AIO_KEY         "6b6ba85da07b45f19bbcc8aacbcb991e"

/************ Global State (you don't need to change this!) ******************/

// Create an ESP8266 WiFiClient class to connect to the MQTT server.
WiFiClient client;  // Must set AIO_SERVERPORT to 1883
// or... use WiFiFlientSecure for SSL
//WiFiClientSecure client;  // Must set AIO_SERVERPORT to 8883

// Setup the MQTT client class by passing in the WiFi client and MQTT server and login details.
Adafruit_MQTT_Client mqtt(&client, AIO_SERVER, AIO_SERVERPORT, AIO_USERNAME, AIO_USERNAME, AIO_KEY);

/****************************** Feeds ***************************************/

// Notice MQTT paths for AIO follow the form: <username>/feeds/<feedkey>
// Feed keys use the lowercase form of the feed name
Adafruit_MQTT_Subscribe device1 = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME "/feeds/device1");
Adafruit_MQTT_Subscribe device2 = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME "/feeds/device2");

/*************************** Sketch Code ************************************/

// Bug workaround for Arduino 1.6.6, it seems to need a function declaration
// for some reason (only affects ESP8266, likely an arduino-builder bug).
void MQTT_connect();

void setup() {
  pinMode(myDeviceOne, OUTPUT);
  pinMode(myDeviceTwo, OUTPUT);

  Serial.begin(9600);
  delay(10);

  Serial.println(F("Adafruit MQTT demo"));

  // Connect to WiFi access point.
  Serial.println(); Serial.println();
  Serial.print("Connecting to ");
  Serial.println(WLAN_SSID);

  WiFi.begin(WLAN_SSID, WLAN_PASS);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();

  Serial.println("WiFi connected");
  Serial.println("IP address: "); Serial.println(WiFi.localIP());

  // Setup MQTT subscription for OnOff feed.
  mqtt.subscribe(&device1);
  mqtt.subscribe(&device2);
}

uint32_t x = 0;

void loop() {
  // Ensure the connection to the MQTT server is alive (this will make the first
  // connection and automatically reconnect when disconnected).  See the MQTT_connect
  // function definition further below.
  MQTT_connect();

  // this is our 'wait for incoming subscription packets' busy subloop
  // try to spend your time here

  Adafruit_MQTT_Subscribe *subscription;
  while ((subscription = mqtt.readSubscription(5000))) {
    // Check if its the OnOff button feed
    if (subscription == &device1) {
      Serial.print(F("Device 1: "));
      Serial.println((char *)device1.lastread);

      if (strcmp((char *)device1.lastread, "ON") == 0) {
        digitalWrite(myDeviceOne, LOW);
      }
      if (strcmp((char *)device1.lastread, "OFF") == 0) {
        digitalWrite(myDeviceOne, HIGH);
      }
    }
    if (subscription == &device2) {
      Serial.print(F("Device 2: "));
      Serial.println((char *)device2.lastread);

      if (strcmp((char *)device2.lastread, "ON") == 0) {
        digitalWrite(myDeviceTwo, LOW);
      }
      if (strcmp((char *)device2.lastread, "OFF") == 0) {
        digitalWrite(myDeviceTwo, HIGH);
      }
    }
  }
}

// Function to connect and reconnect as necessary to the MQTT server.
// Should be called in the loop function and it will take care if connecting.
void MQTT_connect() {
  int8_t ret;

  // Stop if already connected.
  if (mqtt.connected()) {
    return;
  }

  Serial.print("Connecting to MQTT... ");

  uint8_t retries = 3;
  while ((ret = mqtt.connect()) != 0) { // connect will return 0 for connected
    Serial.println(mqtt.connectErrorString(ret));
    Serial.println("Retrying MQTT connection in 5 seconds...");
    mqtt.disconnect();
    delay(5000);  // wait 5 seconds
    retries--;
    if (retries == 0) {
      // basically die and wait for WDT to reset me
      while (1);
    }
  }
  Serial.println("MQTT Connected!");
}
