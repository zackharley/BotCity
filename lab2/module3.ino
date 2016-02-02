#include<Servo.h>

#define PAN_PIN  9
#define TILT_PIN 10
#define GRIP_PIN 8

#define BUTTON_PIN 11
#define SENSOR_PIN 1

#define LED 12

#define GRIP_THRESHOLD 1000

Servo tiltServo, panServo, gripServo;

int buttonValue = 0;
double gripper = 50;
int sensorValue = 0;

int ledLight = 0;

void setup() {

  pinMode(BUTTON_PIN, INPUT);
  pinMode(LED, OUTPUT);
  
  tiltServo.attach(TILT_PIN);
  panServo.attach(PAN_PIN);
  gripServo.attach(GRIP_PIN);
  
  Serial.begin(9600);
}

void loop() {
  buttonValue = digitalRead(BUTTON_PIN);

  while(buttonValue == 0) {

    setPan(90);
    setTilt(70);
    setGrip(gripper);

    delay(1000);
    
    sensorValue = analogRead(SENSOR_PIN);

    while(sensorValue <= GRIP_THRESHOLD) {
      sensorValue = analogRead(SENSOR_PIN);    
      gripper = gripper + .01;
      setGrip(gripper);

      digitalWrite(LED, LOW);
    }
    
    if(sensorValue >= GRIP_THRESHOLD)
      digitalWrite(LED, HIGH);
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


