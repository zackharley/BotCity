#include<Servo.h>
#include<EEPROM.h>
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

#define IRpin 4

byte Lspeed = 0;
byte Rspeed = 0;
int distance = 0;
int adjust = 0;
void setup() {
  pinMode(BUTTON_PIN, INPUT);
  pinMode(LEFT_BUMPER_PIN, INPUT);
  pinMode(RIGHT_BUMPER_PIN, INPUT);
  pinMode(LED, OUTPUT);
  pinMode(RIGHT_MOTOR_SPEED, OUTPUT);
  pinMode(LEFT_MOTOR_SPEED, OUTPUT);
  Serial.begin(9600);
  Serial.println("STARTING");
  Lspeed = EEPROM.read(0);
  Rspeed = EEPROM.read(1);
}

void loop()
{
  while (digitalRead(BUTTON_PIN));
  setMotors(1,Lspeed, 1,Rspeed, -1);
  reactIR();
}

void reactIR() {
  int go = 1;
  while (go) {
    distance = analogRead(IRpin);
    adjust = distance/10;
    Serial.println(distance);
    if(distance>500){
      setMotors(1,0,1,0,-1);
      go=0;
    }
    else{
      setMotors(1,Lspeed-adjust,1,Rspeed-adjust,-1);
    }
  }
}

void setMotors(int Ldir, int Lspd, int Rdir, int Rspd, int rotations) {
  digitalWrite(LEFT_MOTOR_DIRECTION, Ldir);
  analogWrite(LEFT_MOTOR_SPEED,  Lspd);
  digitalWrite(RIGHT_MOTOR_DIRECTION, Rdir);
  analogWrite(RIGHT_MOTOR_SPEED,  Rspd);
  delay(200);
  if (rotations != -1)
    countEncoder(rotations);
}

void countEncoder(int rotations) {
  for (int i = 0; i < rotations; i++) {
    Serial.println(i);
    while (!digitalRead(LEFT_ENCODER));
    while (digitalRead(LEFT_ENCODER));
  }
}

