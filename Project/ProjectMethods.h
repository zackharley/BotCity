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