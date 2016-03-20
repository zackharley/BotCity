#include<Servo.h>

int panPin = 11;
int tiltPin = 12;
int gripPin = 13;

int sensorPin = 1;

int gripThres = 500;

Servo tiltServo, panServo, gripServo;

double grip = 50;
int sensorValue = 0;

void setup() {
  
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
      grip = grip + .5;
      if(grip> 75)
        grip=0;    
      setGrip(grip);
      Serial.println(grip);
     
    }
      grip = 0;
    
      delay(1000);
  
}
void grabBall(){
  while(sensorValue <= gripThres) {
      sensorValue = analogRead(sensorPin);    
      grip = grip + .5;
      if(grip> 75)
        grip=0;  
      setGrip(grip);
      Serial.println(grip);
     
    }
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


