#include<Servo.h>

#define RIGHT_MOTOR_DIRECTION 2
#define RIGHT_MOTOR_SPEED     3
#define LEFT_MOTOR_DIRECTION  4
#define LEFT_MOTOR_SPEED      5


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

int GRIP_THRES = 500;

Servo tiltServo, panServo, gripServo;

int 

void loop() {
    initialize();
}

// Before calling this function ensure that the robot is at the cross on the play field
// with the basket behind it.
void ball0() {
    // Get ball 0
}  // end ball0 function

// Before calling this function ensure that the robot is at the cross on the play field
// with the basket behind it.
void ball1() {
    // Get ball 1
}  // end ball1 function

// Before calling this function ensure that the robot is at the cross on the play field
// with the basket behind it.
void ball2() {
    driveRotate(90, 0);
    driveForward();
    leftBumperValue = checkBumper(0);
    rightBumperValue = checkBumper(1);
    while(leftBumperValue && rightBumperValue){
        leftBumperValue = checkBumper(0);
        rightBumperValue = checkBumper(1);
        delay(100);
    }
    driveStop();
    delay(100);
    driveBackward();
    delay(1000);
    driveStop();
    grabBalls();
    driveBackward();
    while() {
        // Drive until we hit the center
    }
    driveRotate(90, 1);
} // end ball2 function

// 
void setup() {
    setPan(90);
    setTilt(180);
} // end initialize function

// DRIVE FUNCTIONS
// Instruct the motors to drive forward.
void driveForward() {
    digitalWrite(LEFT_MOTOR_DIRECTION, HIGH);
    analogWrite(LEFT_MOTOR_SPEED, 100);
    digitalWrite(RIGHT_MOTOR_DIRECTION, HIGH);
    analogWrite(RIGHT_MOTOR_SPEED, 100);
} // end driveForward function

void driveBackward() {
    digitalWrite(LEFT_MOTOR_DIRECTION, HIGH);
    analogWrite(LEFT_MOTOR_SPEED, 100);
    digitalWrite(RIGHT_MOTOR_DIRECTION, HIGH);
    analogWrite(RIGHT_MOTOR_SPEED, 100);
} // end driveBackward dunction

// Instruct the motors to stop.
void driveStop() {
    digitalWrite(LEFT_MOTOR_DIRECTION, HIGH);
    analogWrite(LEFT_MOTOR_SPEED, 0);
    digitalWrite(RIGHT_MOTOR_DIRECTION, HIGH);
    analogWrite(RIGHT_MOTOR_SPEED, 0);
} // end driveStop function

// Instruct the motors to rotate in a specified direction. Pass in the angle and direction
// as integer values (left is '0' and right is '1').
void driveRotate(int angle, int direction) {
    if(angle == 90 && direction == 0) {
        // Turn left
        digitalWrite(LEFT_MOTOR_DIRECTION, LOW);
        analogWrite(LEFT_MOTOR_SPEED, 100);
        digitalWrite(RIGHT_MOTOR_DIRECTION, HIGH);
        analogWrite(RIGHT_MOTOR_SPEED, 100);
        delay(1000);
    } else if(angle == 90 && direction == 1) {
        // Turn right
        digitalWrite(LEFT_MOTOR_DIRECTION, HIGH);
        analogWrite(LEFT_MOTOR_SPEED, 100);
        digitalWrite(RIGHT_MOTOR_DIRECTION, LOW);
        analogWrite(RIGHT_MOTOR_SPEED, 100);
        delay(1000);
    } else if(angle == 180) {
        // Turn 180 degrees
        digitalWrite(LEFT_MOTOR_DIRECTION, HIGH);
        analogWrite(LEFT_MOTOR_SPEED, 100);
        digitalWrite(RIGHT_MOTOR_DIRECTION, LOW);
        analogWrite(RIGHT_MOTOR_SPEED, 100);
        delay(2000);
    }
} // end driveRotate function

// Check the bumper value. Pass in a '0' for the left bumper or '1' for the right bumper.
// Returns the value of the checked bumper.
int checkBumper(int bumper) {
    if(bumper == 0) {
        return digitalRead(LEFT_BUMPER_PIN);
    } else {
        return digitalRead(RIGHT_BUMPER_PIN);
    }
} // end checkBumpers function

// Sets the pan of the grip to the given angle
void setPan(int angle) {
    panServo.write(angle);
} // end setPan function

// Sets the tilt of the grip to the given angle
void setTilt(int angle) {
    tiltServo.write(angle);
} // end setTilt function

void grabBalls() {
    // Litt's got this
} // end grabBalls function