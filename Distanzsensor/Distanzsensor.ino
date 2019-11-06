/*
 * Distanzsensor von Marlon Loretz
 * Dieses Projekt misst den Abstand zwischen dem Ardunino und einem Objekt.
 * Je nach Distanz werden andere Töne und andere Farben ausgegeben.
 */

// Pins definieren
const int trigPin = 9;
const int echoPin = 10;
const int buzzer = 11;
const int ledRed = 13;
const int ledYellow = 2;
const int ledGreen = 7;

// restliche Variabeln
long duration;
int distance;
int safetyDistance;
int val;

//Setup Methode
void setup() {
  
// Die Pins als Input oder Output deklarieren
pinMode(trigPin, OUTPUT);
pinMode(echoPin, INPUT);
pinMode(buzzer, OUTPUT);
pinMode(ledRed, OUTPUT);
pinMode(ledGreen, OUTPUT);
pinMode(ledYellow, OUTPUT);
Serial.begin(9600);
}

// Loop Methode
void loop() {

// cleard den Distanzmesser
digitalWrite(trigPin, LOW);
delayMicroseconds(2);

// Setzt den TriggerPin auf HIGH für 10 Millisekunden
digitalWrite(trigPin, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin, LOW);

// Liest den EchoPin und misst die Zeit
duration = pulseIn(echoPin, HIGH);

// berechnet die Distanz
distance= duration*0.034/2;

safetyDistance = distance;

// Anfang der IF-Schleife
// Sie gibt für verschiedene Distanzen verschiedene Werte aus
if (safetyDistance <= 3){
  digitalWrite(buzzer, HIGH);
  digitalWrite(ledRed, HIGH);
  delay(10);
  digitalWrite(buzzer, LOW);
  digitalWrite(ledRed, LOW);
  delay(10);
}
else if(safetyDistance <= 6){
  digitalWrite(buzzer, HIGH);
  digitalWrite(ledRed, HIGH);
  digitalWrite(ledYellow, LOW);
  digitalWrite(ledGreen, LOW);
  delay(50);
  digitalWrite(buzzer, LOW);
  digitalWrite(ledRed, LOW);
  digitalWrite(ledYellow, LOW);
  digitalWrite(ledGreen, LOW);
  delay(50);
}
else if(safetyDistance <= 9){
  digitalWrite(buzzer, HIGH);
  digitalWrite(ledRed, LOW);
  digitalWrite(ledYellow, HIGH);
  digitalWrite(ledGreen, LOW);
  delay(100);
  digitalWrite(buzzer, LOW);
  digitalWrite(ledRed, LOW);
  digitalWrite(ledYellow, LOW);
  digitalWrite(ledGreen, LOW);
  delay(100);
}
else if(safetyDistance <= 12){
  digitalWrite(buzzer, HIGH);
  digitalWrite(ledRed, LOW);
  digitalWrite(ledYellow, HIGH);
  digitalWrite(ledGreen, LOW);
  delay(200);
  digitalWrite(buzzer, LOW);
  digitalWrite(ledRed, LOW);
  digitalWrite(ledYellow, LOW);
  digitalWrite(ledGreen, LOW);
  delay(200);
}
else if(safetyDistance <= 15){
  digitalWrite(buzzer, HIGH);
  digitalWrite(ledRed, LOW);
  digitalWrite(ledYellow, HIGH);
  digitalWrite(ledGreen, LOW);
  delay(400);
  digitalWrite(buzzer, LOW);
  digitalWrite(ledRed, LOW);
  digitalWrite(ledYellow, LOW);
  digitalWrite(ledGreen, LOW);
  delay(400);
}
else{
  digitalWrite(buzzer, LOW);
  digitalWrite(ledGreen, HIGH);
  digitalWrite(ledRed, LOW);
  digitalWrite(ledYellow, LOW);
}
}
