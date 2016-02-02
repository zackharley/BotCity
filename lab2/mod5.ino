#include<Servo.h>

#define LEFT_ENCODER 2
#define RIGHT_ENCODER 3

#define RIGHT_MOTOR_SPEED 6
#define RIGHT_MOTOR_DIRECTION 7
#define LEFT_MOTOR_SPEED 5
#define LEFT_MOTOR_DIRECTION 4

#define LEFT_BUMPER_PIN 8
#define RIGHT_BUMPER_PIN 9

#define FULL_SPIN 12

#define BUTTON_PIN 11

#define LED 12

int buttonValue = 0, leftBumperValue = 0, rightBumperValue = 0;
int encoderValue1 = 0, encoderValue2 = 0;
int ledLight = 0;

int turnCount = 0;

void setup() {

  pinMode(BUTTON_PIN, INPUT);
  pinMode(LEFT_BUMPER_PIN, INPUT);
  pinMode(RIGHT_BUMPER_PIN, INPUT);
  pinMode(LED, OUTPUT);

  pinMode(RIGHT_MOTOR_SPEED, OUTPUT);
  pinMode(LEFT_MOTOR_SPEED, OUTPUT);

  waitButton();
  
  Serial.begin(9600);
}

void loop() {
  moveForward();
  delay(200);
  reactBumpers();
}



void waitButton() {
  buttonValue = digitalRead(BUTTON_PIN);
  while(buttonValue == 1) {
    buttonValue = digitalRead(BUTTON_PIN);
    delay(100);
  }
}

void moveForward() {
  digitalWrite(LEFT_MOTOR_DIRECTION, HIGH);
  analogWrite(LEFT_MOTOR_SPEED,  100);
  digitalWrite(RIGHT_MOTOR_DIRECTION, HIGH);
  analogWrite(RIGHT_MOTOR_SPEED,  120);
}

void reactBumpers() {
  leftBumperValue = digitalRead(LEFT_BUMPER_PIN);
  rightBumperValue = digitalRead(RIGHT_BUMPER_PIN);

  if(leftBumperValue == 0 && rightBumperValue == 0) {
    reverse();
    pivot(1, 180);
  } else if(leftBumperValue == 0) {
    reverse();
    pivot(1, 45);
  } else if(rightBumperValue == 0) {
    reverse();
    pivot(0, 45);
  }
}

void reverse() {
  digitalWrite(LEFT_MOTOR_DIRECTION, LOW);
  analogWrite(LEFT_MOTOR_SPEED,  100);
  digitalWrite(RIGHT_MOTOR_DIRECTION, LOW);
  analogWrite(RIGHT_MOTOR_SPEED,  100);

  delay(3000);
}

void pivot(int dir, int angle) {
  // dir = 1 is right, dir = 0 is left
  if(angle > 45){
    while(turnCount <= 20){
        digitalWrite(LEFT_MOTOR_DIRECTION, HIGH);
        analogWrite(LEFT_MOTOR_SPEED,  100);
        analogWrite(RIGHT_MOTOR_SPEED,  0);
        countEncoder(0);
    }
    turnCount = 0;
  }
  
  if(dir == 1){
    while(turnCount <= 5){
        digitalWrite(LEFT_MOTOR_DIRECTION, HIGH);
        analogWrite(LEFT_MOTOR_SPEED,  100);
        analogWrite(RIGHT_MOTOR_SPEED,  0);
        countEncoder(0);
    }
    turnCount = 0;
  } else {
    while(turnCount <= 5){
        digitalWrite(RIGHT_MOTOR_DIRECTION, HIGH);
        analogWrite(RIGHT_MOTOR_SPEED,  100);
        analogWrite(LEFT_MOTOR_SPEED,  0);
        countEncoder(1);
    }
    turnCount = 0;
  }
}

void countEncoder(int encoder) {
  if(encoder == 1){
      encoderValue2 = digitalRead(RIGHT_ENCODER);
    
      if(encoderValue1 == 0 && encoderValue2 == 1)
         turnCount++;
  
      encoderValue1 = encoderValue2;
  } else {
      encoderValue2 = digitalRead(LEFT_ENCODER);
    
      if(encoderValue1 == 0 && encoderValue2 == 1)
        turnCount++;
  
      encoderValue1 = encoderValue2;
  }
}

