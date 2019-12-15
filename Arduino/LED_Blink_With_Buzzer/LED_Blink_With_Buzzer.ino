
/* Arduino Built In LED Blink_With_Buzzer

   GitHub URL - https://github.com/narayanvyas/IoT-workshop

   Components
   ----------
    - Arduino Uno R3
    - One LEDs
    - One 220 Ohm Resistor
    - Breadboard

   Connections
   -----------
        Break out          |     Arduino Uno
   --------------------------------------------
        LED OUT      |        4

     Also connect LEDs to 220 Ohm Resistor.

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

  delay - Pauses the program for the amount of time (in milliseconds) specified as parameter. (There are 1000 milliseconds in a second.)
*/

int ledPin = 4;
int buzzer=5;

void setup() {
  Serial.println(9600);  // Initializing Serial Monitor
  pinMode(ledPin , OUTPUT); // Setting LED as Output Device
  pinMode(buzzer , OUTPUT); // Setting Buzzer as Output Device
}

void loop() {
  Serial.println("Turning LED On");
  digitalWrite(ledPin, HIGH);  // Turning LED On
  tone(buzzer,1000);//buzzer beep starts
  delay(1000); // Setting Delay of 1 Second
  Serial.println("Turning LED Off");
  digitalWrite(ledPin, LOW);  // Turning LED Off
  noTone(buzzer);//buzzer beep stops
  delay(1000); // Setting Delay of 1 Second
  
}
