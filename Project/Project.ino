////////////////////////////
//ELEC299-Winter2016
//////////////////////////////
// “Project”
//
//  Group#:48
//
//  Group Members:
//  AndrewLitt(10150478)
//  ZackHarley(10135795)
//  KieranMackenzie(10149822)
//////////////////////////////
#include <Servo.h>
#include <QSerial.h>
//  PIN CONFIGURATION

// MOTOR ENCODERS & CONTROLLERS
#define RIGHT_MOTOR_DIRECTION 2
#define RIGHT_MOTOR_SPEED     3
#define LEFT_MOTOR_DIRECTION  4
#define LEFT_MOTOR_SPEED      5
#define IRreciever            6

// GRIPPER 
#define PAN                   11
#define TILT                  12
#define GRIP                  13

//ANALOG PIN LAYOUT
#define gripRead              1
#define left                  2
#define right                 3
#define middle                4
#define IRsensor              5

//DEFINED CONSTANTS
#define gripThres            500
#define maxGripAngle         75

//VARIABLE DECLARATION
int gripValue = 0;
double gripAngle = 50;
int lLev = 0;
int rLev = 0;
int mLev = 0;
int distance = 0;
Servo tiltServo, panServo, gripServo;
QSerial IRserial;

void setup() {
  Serial.begin(9600);
  pinMode(IRreciever,INPUT);
  pinMode(RIGHT_MOTOR_SPEED, OUTPUT);
  pinMode(LEFT_MOTOR_SPEED, OUTPUT);
  
  panServo.attach(PAN);
  tiltServo.attach(TILT);
  gripServo.attach(GRIP);
  IRserial.attach(IRreciever,-1);
  
  setTilt(180);
  setPan(90);
  setGrip(0);
  delay(500);
}

void loop() {
  // put your main code here, to run repeatedly:
  grabBall();
  while(true);
  //getAnalogReadings();
  //delay(1000);
  
}
void getAnalogReadings(){
  gripValue = analogRead(gripRead);
  distance = analogRead(IRsensor);
  lLev = analogRead(left);
  rLev = analogRead(right);
  mLev = analogRead(middle);
  Serial.print("Left: ");
  Serial.println(lLev);
  Serial.print("Middle: ");
  Serial.println(mLev);
  Serial.print("Right: ");
  Serial.println(rLev);
  Serial.print("Distance: ");
  Serial.println(distance);
  Serial.print("Grip Value: ");
  Serial.println(gripValue);
  Serial.print("\n");
}
//METHODS
//SECTION 1: BASIC MOTOR CONTROL

void grabBall(){
  setPan(90);
  lowerArm();
  while(gripValue <= gripThres) {
      gripValue = analogRead(gripRead);    
      gripAngle = gripAngle + .5;
      
      if(gripAngle > maxGripAngle){
        gripAngle=0;
        setGrip(0);
        delay(200);
        setTilt(180);
        lowerArm();
      }
      setGrip(gripAngle);
      Serial.println(gripAngle);
    }
  setTilt(180);
}

void lowerArm(){
  float angle = 180;
  while(angle>=75){
    angle = angle - 0.01;
    setTilt(angle);
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
