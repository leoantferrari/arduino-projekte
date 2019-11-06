/*
 * Linienfolger von Leo Ferrari und Marlon Loretz
 * Der Linienfolger kalibriert zuerst die Farben und kann dadurch
 * einer Linie Folgen.
 */

// Imports
#include <TimerOne.h>
#include <Wire.h>
#include <Zumo32U4.h>

// definiert die weiteren notwendigen Elemente
Zumo32U4Motors motors;
Zumo32U4LCD lcd;
Zumo32U4LineSensors lineSensors;
Zumo32U4Encoders encoders;

// Setup-Methode
void setup() {

// kalibriert die Sensoren
  lineSensors.initFiveSensors();
  calibrateLineSensors();
  lcd.gotoXY(0, 1);  
}
// Methode zur Kalibrierung
void calibrateLineSensors(){
 ledYellow(1);
 lcd.clear();
 lcd.print(F("Line cal"));

// während der Kalibrierung fährt der Zumo herum, um alle Farben zu erwischen
 for (uint16_t i = 0; i < 400; i++)
 {
  if(i<=100){
  motors.setLeftSpeed(200);
  motors.setRightSpeed(200);
  }
  else if(i<=200){
  motors.setLeftSpeed(-200);
  motors.setRightSpeed(-200);
  }
  else if(i<=300){
  motors.setLeftSpeed(200);
  motors.setRightSpeed(-200);
  }
  else if(i<=400){
  motors.setLeftSpeed(-200);
  motors.setRightSpeed(200);
  }
  
 lcd.gotoXY(0, 1);
 lcd.print(i);
 lineSensors.calibrate();
 }
 ledYellow(0);
 lcd.clear();
}

// Loop-Methode
void loop(){

// misst die Werte und entscheidet wie schnell jeder Motor sein muss
  uint16_t lineSensorValues[5] = { 0, 0, 0, 0, 0 };
  lineSensors.readCalibrated(lineSensorValues);
  if(lineSensorValues[1] < 400 && lineSensorValues[3] > 400) {
     motors.setLeftSpeed(300);
     motors.setRightSpeed(300);
  }
  else if(lineSensorValues[1] > 400 ){
     motors.setLeftSpeed(-100);
     motors.setRightSpeed(200);
  }
  else if(lineSensorValues[1] < 400 && lineSensorValues[3] < 400){
     motors.setLeftSpeed(200);
     motors.setRightSpeed(-100);
  }
}
