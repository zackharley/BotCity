#include<Servo.h>

#define LEFT_ENCODER 2
#define RIGHT_ENCODER 3

#define RIGHT_MOTOR_SPEED 6
#define RIGHT_MOTOR_DIRECTION 7
#define LEFT_MOTOR_SPEED 5
#define LEFT_MOTOR_DIRECTION 4

#define FULL_SPIN 12

#define BUTTON_PIN 11

#define LED 12

int buttonValue = 0;
int encoderValue1 = 0, encoderValue2 = 0;
int ledLight = 0;

int turnCount = 0;

void setup() {

  pinMode(BUTTON_PIN, INPUT);
  pinMode(LED, OUTPUT);

  pinMode(RIGHT_MOTOR_SPEED, OUTPUT);
  pinMode(LEFT_MOTOR_SPEED, OUTPUT);
  
  Serial.begin(9600);
}

void loop() {
  buttonValue = digitalRead(BUTTON_PIN);

  while(buttonValue == 0) {

    countEncoder();

    while(turnCount <= (3 * FULL_SPIN)) {
      digitalWrite(LEFT_MOTOR_DIRECTION, HIGH);
      analogWrite(LEFT_MOTOR_SPEED,  100);
      digitalWrite(RIGHT_MOTOR_DIRECTION, HIGH);
      analogWrite(RIGHT_MOTOR_SPEED,  120);
      countEncoder();
    }

    turnCount = 0;

    while(turnCount <= (2 * FULL_SPIN)) {
      digitalWrite(LEFT_MOTOR_DIRECTION, LOW);
      analogWrite(LEFT_MOTOR_SPEED,  100);
      digitalWrite(RIGHT_MOTOR_DIRECTION, LOW);
      analogWrite(RIGHT_MOTOR_SPEED,  100);
      countEncoder();
    }

    turnCount = 0;

    while(turnCount <= (FULL_SPIN/4)) {
      digitalWrite(LEFT_MOTOR_DIRECTION, HIGH);
      analogWrite(LEFT_MOTOR_SPEED,  100);
      countEncoder();
    }

    analogWrite(LEFT_MOTOR_SPEED,  0);
    analogWrite(RIGHT_MOTOR_SPEED,  0);

    digitalWrite(LED, HIGH);
    
    break;
  }
}

void countEncoder() {
  encoderValue2 = digitalRead(LEFT_ENCODER);
    
  if(encoderValue1 == 0 && encoderValue2 == 1)
   turnCount++;
  
  encoderValue1 = encoderValue2;
}


