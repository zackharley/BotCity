#include<Servo.h>

int panPin = 11;
int tiltPin = 10;
int gripPin = 12;

int sensorPin = 5;
int LEDpin = 13;

int gripThres = 500;

Servo tiltServo, panServo, gripServo;

double grip = 50;
int sensorValue = 0;

void setup() {

  pinMode(LEDpin, OUTPUT);
  
  tiltServo.attach(tiltPin);
  panServo.attach(panPin);
  gripServo.attach(gripPin);
  
  setPan(90);
  setTilt(180);
  
  Serial.begin(9600);
}

void loop() {

    //setPan(90);
    setTilt(180);
    setGrip(grip);

    delay(1000);
    
    sensorValue = analogRead(sensorPin);

    while(sensorValue <= gripThres) {
      sensorValue = analogRead(sensorPin);    
      grip = grip + .05;
      setGrip(grip);
      Serial.println(sensorValue);
      digitalWrite(LEDpin, LOW);
    }
      grip = 0;
      digitalWrite(LEDpin, HIGH);
      delay(1000);
  
}

void setPan(int angle) {
  panServo.write(angle);
}

void setGrip(int angle) {
  gripServo.write(angle);
}

void setTilt(int angle) {
  tiltServo.write(angle);
}


