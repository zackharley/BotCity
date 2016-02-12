#include<Servo.h>

#define LEFT_ENCODER 2
#define RIGHT_ENCODER 3

#define RIGHT_MOTOR_SPEED 6
#define RIGHT_MOTOR_DIRECTION 7
#define LEFT_MOTOR_SPEED 5
#define LEFT_MOTOR_DIRECTION 4

#define LEFT_BUMPER_PIN 8
#define RIGHT_BUMPER_PIN 9

#define FULL_SPIN 9

#define BUTTON_PIN 13

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
  Serial.begin(9600);
  while (digitalRead(BUTTON_PIN));
}

void loop()
{
  setMotors(1, 1, -1);
  reactBumpers();
}

void setMotors(int Ldir, int Rdir, int rotations) {
  digitalWrite(LEFT_MOTOR_DIRECTION, Ldir);
  analogWrite(LEFT_MOTOR_SPEED,  100);
  digitalWrite(RIGHT_MOTOR_DIRECTION, Rdir);
  analogWrite(RIGHT_MOTOR_SPEED,  100);
  delay(200);
  if (rotations != -1)
    countEncoder(rotations);
}

void reactBumpers() {
  while (true) {
    delay(2000);
    leftBumperValue = digitalRead(LEFT_BUMPER_PIN);
    
    rightBumperValue = digitalRead(RIGHT_BUMPER_PIN);
    
    Serial.println(leftBumperValue);
    Serial.println(rightBumperValue);
  
    if (!leftBumperValue && !rightBumperValue) {
      Serial.println("Both");
      setMotors(0, 0, FULL_SPIN);
      setMotors(1, 0, FULL_SPIN);
      
      break;
    }
    else if (!leftBumperValue) {
      setMotors(0, 0, FULL_SPIN);
      setMotors(1, 0, FULL_SPIN/4);
      Serial.println("Left");
      break;
    }
    else if (!rightBumperValue) {
      setMotors(0, 0, FULL_SPIN);
      setMotors(0, 1, FULL_SPIN/4);
      Serial.println("Right");
      break;
    }
  }
}

void countEncoder(int rotations) {
  for (int i = 0; i < rotations; i++) {
    Serial.println(i);
    while (!digitalRead(LEFT_ENCODER));
    while (digitalRead(LEFT_ENCODER));
  }
}


