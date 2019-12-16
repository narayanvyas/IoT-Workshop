#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
#include <ESP8266WiFi.h>    // Header File for ESP8266 NodeMCU
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"

/* Set these to your desired credentials. */
const char *ssid = "Redmi";
const char *password = "123456789";

#define SEALEVELPRESSURE_HPA (1013.25)
unsigned status;
float c, h, p, a;

/* Adafruit Setup */
#define AIO_SERVER      "io.adafruit.com"
#define AIO_SERVERPORT  1883                   // use 8883 for SSL
#define AIO_USERNAME    "narayanvyas"
#define AIO_KEY         "6b6ba85da07b45f19bbcc8aacbcb991e"

WiFiClient client;
Adafruit_MQTT_Client mqtt(&client, AIO_SERVER, AIO_SERVERPORT, AIO_USERNAME, AIO_KEY);
Adafruit_MQTT_Publish celsius = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/celsius");
Adafruit_MQTT_Publish humidity = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/humidity");
Adafruit_MQTT_Publish pressure = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/pressure");
Adafruit_MQTT_Publish alt = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/altitude");
void MQTT_connect();

Adafruit_BME280 bme; // I2C
void setup() {
  Serial.begin(9600);
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
  status = bme.begin();

  if (!status) {
    Serial.println("Could not find a valid BME280 sensor, check wiring, address, sensor ID!");
    Serial.print("SensorID was: 0x"); Serial.println(bme.sensorID(), 16);
    Serial.print("        ID of 0xFF probably means a bad address, a BMP 180 or BMP 085\n");
    Serial.print("   ID of 0x56-0x58 represents a BMP 280,\n");
    Serial.print("        ID of 0x60 represents a BME 280.\n");
    Serial.print("        ID of 0x61 represents a BME 680.\n");
    while (1);
  }

  Serial.println();
}


void loop() {
  printValues();
  delay(1000);
}


void printValues() {
  c = bme.readTemperature();
  h = bme.readHumidity();
  p = bme.readPressure() / 100.0F;
  a = bme.readAltitude(SEALEVELPRESSURE_HPA);
  
  Serial.print("Temperature = ");
  Serial.print(c);
  Serial.println(" *C");

  Serial.print("Pressure = ");

  Serial.print(p / 100.0F);
  Serial.println(" hPa");

  Serial.print("Approx. Altitude = ");
  Serial.print(a);
  Serial.println(" m");

  Serial.print("Humidity = ");
  Serial.print(h);
  Serial.println(" %");

  Serial.println();

  handleMQTT();
  delay(5000);
}

void handleMQTT() {
  MQTT_connect();
  if (!celsius.publish(c)) {
    Serial.println(F("Failed"));
  } else {
    Serial.println(F("Sent"));
  }
  delay(1500);
  if (!humidity.publish(h)) {
    Serial.println(F("Failed"));
  } else {
    Serial.println(F("Sent"));
  }
  delay(1500);
  if (!pressure.publish(p)) {
    Serial.println(F("Failed"));
  } else {
    Serial.println(F("Sent"));
  }
  delay(1500);
  if (!alt.publish(a)) {
    Serial.println(F("Failed"));
  } else {
    Serial.println(F("Sent"));
  }
  delay(1500);
}

void MQTT_connect() {
  int8_t ret;
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
      while (1);
    }
  }
  Serial.println("MQTT Connected!");
}
