/* Flame Detector With Arduino

   GitHub URL - https://github.com/narayanvyas/IoT-workshop

   Components
   ----------
    - Arduino Uno R3
    - Flame Sensor
    - Two LEDs
    - Two 220 Ohm Resistors
    - A Buzzer
    - PCB / Breadboard
    - Wires

   Connections
   -----------
        Break out          |     Arduino Uno
   --------------------------------------------
        Flame Sensor VCC   |        5V
        Flame Sensor GND   |        GND
        Flame Sensor Pin   |        8
        Buzzer GND         |        GND
        Buzzer OUT         |        2
        Red LED OUT        |        3
        Green LED OUT      |        4

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

int sensorPin = 8;    // Variable to control Flame Sensor (Data will be received in Digital Form)
int buzzer = 2;
int redLed = 3;
int greenLed = 4;
int sensorValue;

void setup() {
  Serial.begin(9600);  // Initializing Serial Monitor

  // Setting up pin modes
  pinMode(sensorPin, INPUT); // Setting sensor as Input Device
  pinMode(buzzer, OUTPUT);  // Setting buzzer as Output Device
  pinMode(greenLed, OUTPUT);
  pinMode(redLed, OUTPUT);

  lightShow();  // Calling the lightshow method, which will turn leds on and off while starting the device
}

void loop() {
  sensorValue = digitalRead(sensorPin);  // Reading the sensor value
  Serial.println(sensorValue);  // Printing the sensor value to Serial Monnito

  if (sensorValue == 0)
  {
    tone(buzzer, 1000); // Turning Buzzer on with frequency of 1000
    digitalWrite(redLed, HIGH); // Turning LED On
    digitalWrite(greenLed, LOW);  // Turning LED Off

  }
  else
  {
    noTone(buzzer); // Turning off the Buzzer
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
