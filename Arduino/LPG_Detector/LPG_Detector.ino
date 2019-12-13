/* LPG Leakage Detector With MQ - 6 Sensor

   GitHub URL - https://github.com/narayanvyas/IoT-workshop

   Components
   ----------
    - Arduino Uno R3
    - MQ-6 Sensor
    - Two LEDs
    - Two 220 Ohm Resistors
    - A Buzzer
    - PCB / Breadboard
    - Wires

   Connections
   -----------
        Break out          |     Arduino Uno
   --------------------------------------------
        MQ6 VCC            |        5V
        MQ6 GND            |        GND
        MQ6 Analog Pin     |        A2
        Red LED OUT        |        5
        Green LED OUT      |        6
        Buzzer GND         |        GND
        Buzzer OUT         |        7

     Also connect LEDs two 220 Ohm Resistors.

         ----/\/\/\/\----(LED |)----GND
*/

/* Method Documentation
  
  setup - The setup() function is called when a sketch starts. Use it to initialize variables, pin modes, start using libraries, etc.
          The setup() function will only run once, after each powerup or reset of the Arduino board.

  loop - After creating a setup() function, which initializes and sets the initial values, the loop() function does precisely what its name suggests, and loops consecutively, allowing your program to change and respond.
  
  Serial.begin(9600) - Sets the data rate in bits per second (baud) for serial data transmission, default is 9600

  Serial.print - Prints data to serial monitor

  Serial.println - Prints data to serial monitor on next line
  
  pinMode - Configures the specified pin to behave either as an input or an output. It takes two arguments
            First arguments tells the name of pin, and second argument tells the type of pin, either INPUT or OUTPUT
  
  digitalWrite - Write a HIGH or a LOW value to a digital pin. It takes two arguments
                 First arguments tells the name of pin, and second argument tells the state of pin, either HIGH or LOW
  
  analogWrite - Writes an analog value to a pin. It takes only one argument which is name of pin.
  
  digitalRead - Reads the value from a specified digital pin, either HIGH or LOW. It takes only one argument which is name of pin.
  
  analogRead - Reads the value from the specified analog pin. It takes only one argument which is name of pin.

  tone - Generates a square wave of the specified frequency (and 50% duty cycle) on a pin. A duration can be specified, otherwise the wave continues until a call to noTone(). The pin can be connected to a piezo buzzer or other speaker to play tones.
         syntax 1 - tone(pin, frequency)
         syntax 2 - tone(pin, frequency, duration)
  noTone - Stops the generation of a square wave triggered by tone(). Has no effect if no tone is being generated.
           It takes only one argument which is name
           
  delay - Pauses the program for the amount of time (in milliseconds) specified as parameter. (There are 1000 milliseconds in a second.)
*/

// Global Varibales
int buzzer = 7;
int sensor = A3;  // Variable to control Gas Sensor (MQ 6 - Data will be received in Analog Form)
int redLed = 5;
int greenLed = 6;
int sensorValue;

void setup() {
  Serial.begin(9600);  // Initializing Serial Monitor

  // Setting up pin modes
  pinMode(sensor, INPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(redLed, OUTPUT);
  pinMode(greenLed, OUTPUT);

  lightShow();  // Calling the lightshow method, which will turn leds on and off while starting the device
}

void loop() {
  sensorValue = analogRead(sensor);  // Reading the sensor value
  Serial.println(sensorValue);

  if (sensorValue > 200) {
    tone(buzzer, 1000);
    digitalWrite(redLed, HIGH);
    digitalWrite(greenLed, LOW);
  }
  else {
    noTone(buzzer);
    digitalWrite(redLed, LOW);
    digitalWrite(greenLed, HIGH);
  }
  delay(500);
}

void lightShow() {
  digitalWrite(redLed, LOW);
  digitalWrite(greenLed, HIGH);
  tone(buzzer, 500);
  delay(500);
  digitalWrite(redLed, HIGH);
  digitalWrite(greenLed, LOW);
  noTone(buzzer);
  delay(500);
  digitalWrite(redLed, LOW);
  digitalWrite(greenLed, HIGH);
  tone(buzzer, 500);
  delay(500);
  digitalWrite(redLed, HIGH);
  digitalWrite(greenLed, LOW);
  noTone(buzzer);
  delay(500);
  digitalWrite(redLed, LOW);
  digitalWrite(greenLed, HIGH);
  tone(buzzer, 500);
  delay(500);
  digitalWrite(redLed, HIGH);
  digitalWrite(greenLed, LOW);
  noTone(buzzer);
  delay(500);
}
