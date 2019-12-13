// Varibales
int buzzer = 7;
int sensor = A3;
int greenLed = 6;
int redLed = 5;

void setup() {
  Serial.begin(9600);
  pinMode(sensor, INPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(redLed, OUTPUT);
  pinMode(greenLed, OUTPUT);
  lightShow();
}

void loop() {
  int sensorValue = analogRead(sensor);
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
