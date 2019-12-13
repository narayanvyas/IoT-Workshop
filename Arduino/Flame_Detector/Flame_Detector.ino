int sensor = 7;
int buzzer = 2;
int ledgreen = 4;
int ledred = 3;

void setup() {
  Serial.begin(9600);

  pinMode(sensor, INPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(ledgreen, OUTPUT);
  pinMode(ledred, OUTPUT);

  digitalWrite(ledgreen, HIGH);
  digitalWrite(ledred, HIGH);
  delay(1000);
  digitalWrite(ledgreen, LOW);
  digitalWrite(ledred, LOW);
  delay(1000);
  digitalWrite(ledgreen, HIGH);
  digitalWrite(ledred, HIGH);
  delay(1000);
  digitalWrite(ledred, LOW);
  

}
int output;
void loop() {
  output = digitalRead(sensor);
  Serial.println(output);
  if(output==0)
  {
    digitalWrite(ledred,HIGH);
    digitalWrite(ledgreen,LOW);
    tone(buzzer,1000);
    
    }
  else
  {
    digitalWrite(ledred,LOW);
    digitalWrite(ledgreen,HIGH);
    noTone(buzzer);
    
    }
  delay(500);
}
