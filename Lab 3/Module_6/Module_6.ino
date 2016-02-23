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

#define DELTA 10

int buttonValue = 0, leftBumperValue = 0, rightBumperValue = 0;
int encoderValue1 = 0, encoderValue2 = 0;
int ledLight = 0;

int turnCount = 0;

byte Lspeed = 0;
byte Rspeed = 0;



void setup() {
  pinMode(BUTTON_PIN, INPUT);
  pinMode(LEFT_BUMPER_PIN, INPUT);
  pinMode(RIGHT_BUMPER_PIN, INPUT);
  pinMode(LED, OUTPUT);
  pinMode(RIGHT_MOTOR_SPEED, OUTPUT);
  pinMode(LEFT_MOTOR_SPEED, OUTPUT);
  Serial.begin(9600);
  Lspeed = EEPROM.read(0);
  Rspeed = EEPROM.read(1);
}

void loop()
{
  while (digitalRead(BUTTON_PIN));
  setMotors(1,Lspeed,1,Rspeed, -1);
  AdjustSpeeds();
  setMotors(1,0,1,0,-1);
}

void AdjustSpeeds() {
  Lspeed = 100;
  Rspeed = 100;
  int go = 1;
  while (go==1) {
    delay(2000);
    leftBumperValue = digitalRead(LEFT_BUMPER_PIN);
    rightBumperValue = digitalRead(RIGHT_BUMPER_PIN);

    Serial.println(leftBumperValue);
    Serial.println(rightBumperValue);
  
    if (!leftBumperValue && !rightBumperValue) {
      Serial.println("Both");
      Serial.print("Saving speeds to EEPROM...");
      EEPROM.write(0,Lspeed);
      EEPROM.write(1,Rspeed);
      delay(100);
      Serial.print("Done.\n");
      Serial.print("Left Speed:");
      Serial.print(Lspeed);
      Serial.print("\nRight Speed:");
      Serial.print(Rspeed);
      go=0;
    }
    else if (!leftBumperValue) {
      
      Lspeed = Lspeed - 10;
      Rspeed = Rspeed + 10;
      setMotors(1,Lspeed,1,Rspeed,-1);
      Serial.println("Left");
    }
    else if (!rightBumperValue) {
      Lspeed = Lspeed + 10;
      Rspeed = Rspeed - 10;
      setMotors(1,Lspeed,1,Rspeed,-1);
      Serial.println("Right");
    }
  }
  Serial.println("Exited Main Loop");
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


