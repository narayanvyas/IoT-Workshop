/*  Ultrasonic Distance Sensor With Servo Motor
 * 
 *  GitHub URL - https://github.com/narayanvyas/IoT-workshop
 * 
 * Components
 * ----------
 *  - Arduino Uno
 *  - Ultrasonic Distance Sensor
 *  - An LED
 *  - A 220 Ohm resistor
 *  - A Buzzer
 *  - A Servo Motor
 *  - Jumper Wires
 *  - Breadboard
 *  
 *  Libraries
 *  ---------
 *  - None
 *
 * Connections
 * -----------
 *                   Break out    |    Arduino Uno
 *  --------------------------------------------
 *      Ultrasonic VCC            |        5V
 *      Ultrasonic GND            |        GND
 *      Ultrasonic Echo           |        4
 *      Ultrasonic Trigger        |        3
 *      Servo VCC VCC             |        5V
 *      Servo GND                 |        GND
 *      Servo Out                 |        5
 *      Buzzer GND                |        GND
 *      Buzzer Out                |        8
 *      LED                       |        7
 *      
 * Also connect an LED to simulate a controlled device. 
 *           220 Ohm
 *    3 ----/\/\/\/\----(LED |)----GND
 *  
 */

#include <Servo.h>      // Loading Servo Motor Header Files

#define echoPin 4       // This pin send ultrasonic waves
#define trigPin 3       // This pin gets triggered when it receive returned ultrasonic waves
int ledPin   = 7;       // choose the pin for the LED
int buzzer = 8;         // choose pin for the buzzer
int servoPin = 6;       // Servo Pin

Servo Servo1;           // creating servo object

void setup() {
  Serial.begin (9600);
  pinMode(ledPin, OUTPUT);      // declare LED as output
  pinMode(trigPin, OUTPUT);     //declare Trigger as output
  pinMode(echoPin, INPUT);      //declare echo as Input
  pinMode(buzzer, OUTPUT);     // declare buzzer as output
  Servo1.attach(servoPin);     // attaching servo pin
}

void loop() {
  long duration, distance;    // declare variables for duration and distance calculation
  digitalWrite(trigPin, LOW); // set trigger pin to Low  
  delayMicroseconds(2);       // setting delay in microseconds
  digitalWrite(trigPin, HIGH);  // set trigger pin to High  
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW); // set trigger pin to Low
  duration = pulseIn(echoPin, HIGH);  // calculating duration
  distance = (duration/2) / 29.1; //calculating Distance

//Checking distance conditions
  if (distance >= 100 || distance <= 0){
    Serial.println("Out of range");
    digitalWrite(ledPin, LOW); // turn LED OFF
    noTone(buzzer);
    Servo1.write(0);
  }
  else {
    Serial.print("Object is ");
    Serial.print(distance);
    Serial.print(" cm");
    Serial.println(" far from the machine"); 
    digitalWrite(ledPin, HIGH);  // turn LED ON
    tone(buzzer, 1000);
    Servo1.write(180); //moving motor
    Serial.println("Arm Moved");
    delay(2000);
  }
  delay(200);
}
