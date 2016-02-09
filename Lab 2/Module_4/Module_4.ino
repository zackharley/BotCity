#include<Servo.h>

#define LEFT_ENCODER 2
#define RIGHT_ENCODER 3

#define RIGHT_MOTOR_SPEED 6
#define RIGHT_MOTOR_DIRECTION 7
#define LEFT_MOTOR_SPEED 5
#define LEFT_MOTOR_DIRECTION 4

#define FULL_SPIN 9

#define BUTTON_PIN 13

#define LED 12

int buttonValue = 0;
int encoderValue1 = 0, encoderValue2 = 0;
int ledLight = 0;

int turnCount = 0;

void setup() {

  pinMode(RIGHT_MOTOR_SPEED, OUTPUT);
  pinMode(LEFT_MOTOR_SPEED, OUTPUT);
  pinMode(BUTTON_PIN,INPUT);
  
  Serial.begin(9600);
}

void loop() {
  
      while(digitalRead(BUTTON_PIN));
      
      digitalWrite(LEFT_MOTOR_DIRECTION, HIGH);
      analogWrite(LEFT_MOTOR_SPEED,  100);
      digitalWrite(RIGHT_MOTOR_DIRECTION, HIGH);
      analogWrite(RIGHT_MOTOR_SPEED,  100);
      countEncoderL(FULL_SPIN*3);
      
      digitalWrite(LEFT_MOTOR_DIRECTION, LOW);
      analogWrite(LEFT_MOTOR_SPEED,  100);
      digitalWrite(RIGHT_MOTOR_DIRECTION, LOW);
      analogWrite(RIGHT_MOTOR_SPEED,  100);
      countEncoderL(FULL_SPIN*3);

      digitalWrite(LEFT_MOTOR_DIRECTION, HIGH);
      analogWrite(LEFT_MOTOR_SPEED,  100);
      countEncoderL(FULL_SPIN/3);
      
      digitalWrite(LEFT_MOTOR_DIRECTION, LOW);
      analogWrite(LEFT_MOTOR_SPEED,  0);
      digitalWrite(RIGHT_MOTOR_DIRECTION, LOW);
      analogWrite(RIGHT_MOTOR_SPEED,  0);
      delay(5000);
}

void countEncoderL(int rotations) {
      for(int i = 0; i < rotations; i++){
        Serial.println(i);
        while(!digitalRead(LEFT_ENCODER));
        while(digitalRead(LEFT_ENCODER));
      }
}



