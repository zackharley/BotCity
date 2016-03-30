//////////////////////////////
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
#define LEFT_BUMPER_PIN       7
#define RIGHT_BUMPER_PIN      8

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
#define colourThres          900

//VARIABLE DECLARATION
int gripValue = 0;
double gripAngle = 50;
int lLev = 0;
int rLev = 0;
int mLev = 0;
int lPrev = 0;
int rPrev = 0;
int mPrev = 0;
int distance = 0;
int IRval = -1;
int lBump = 0;
int rBump = 0;
int lSpeed = 100;
int rSpeed = 100;
Servo tiltServo, panServo, gripServo;
QSerial IRserial;

void setup() {
  Serial.begin(9600);
  pinMode(IRreciever,INPUT);
  pinMode(RIGHT_MOTOR_SPEED, OUTPUT);
  pinMode(LEFT_MOTOR_SPEED, OUTPUT);
  pinMode(LEFT_BUMPER_PIN, INPUT);
  pinMode(RIGHT_BUMPER_PIN, INPUT);
  
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
  lineTrack();
  while(true);
}
void getAnalogReadings(){
  //IRreceive();
  gripValue = analogRead(gripRead);
  distance = analogRead(IRsensor);
  lLev =  getColor(left);
  rLev =  getColor(right);
  mLev =  getColor(middle);
  lBump = digitalRead(LEFT_BUMPER_PIN);
  rBump = digitalRead(RIGHT_BUMPER_PIN);
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
  Serial.print("Left Bumper: ");
  Serial.println(lBump);
  Serial.print("Right Bumper: ");
  Serial.println(rBump);
  Serial.print("Recieved Character: ");
  Serial.println(IRval);
  Serial.print("\n");
  delay(1000);
}
//METHODS
//SECTION 1: BASIC MOTOR CONTROL
void IRreceive(){
  IRval = -1;
  while(IRval > 2 || IRval <0){
  IRval = IRserial.receive(200);
  IRval = IRval - 48;
  }
}
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
void start(){
  setMotors(
}
void lineTrack(){
  lBump = digitalRead(LEFT_BUMPER_PIN);
  rBump = digitalRead(RIGHT_BUMPER_PIN);
  while(lBump==1 && rBump == 1){
    lLev = getColor(left);
    rLev = getColor(right);
    mLev = getColor(middle);

    if(!lLev && mLev && !rLev){
      lSpeed = 80;
      rSpeed = 80;
      setMotors(1,1);
    }
    else if(lLev && !mLev && !rLev){
      lSpeed = 85;
      rSpeed = 75;
      setMotors(1,1);
    }
    else if(!lLev && !mLev && rLev){
      lSpeed = 75;
      rSpeed = 85;
      setMotors(1,1);
    }
    else{
      
    }
    
    lBump = digitalRead(LEFT_BUMPER_PIN);
    rBump = digitalRead(RIGHT_BUMPER_PIN);
    
    lPrev = lLev;
    rPrev = rLev;
    mPrev = mLev;
    
  }
  lSpeed = 0;
  rSpeed = 0;
  setMotors(1,1);  
}
void lowerArm(){
  float angle = 180;
  while(angle>=75){
    angle = angle - 0.01;
    setTilt(angle);
  }  
}
int getColor(int pin){
  if(analogRead(pin)>colourThres)
    return  1;
  return 0;
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
void setMotors(int Ldir, int Rdir) {
  digitalWrite(LEFT_MOTOR_DIRECTION, Ldir);
  analogWrite(LEFT_MOTOR_SPEED,lSpeed);
  digitalWrite(RIGHT_MOTOR_DIRECTION, Rdir);
  analogWrite(RIGHT_MOTOR_SPEED,rSpeed);
  delay(200);
}
