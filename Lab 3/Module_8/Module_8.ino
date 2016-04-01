#include <QSerial.h>
QSerial IRserial;

void setup() {
  // put your setup code here, to run once:
  pinMode(9,INPUT);
  IRserial.attach(9,-1);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  int val = IRserial.receive(200);
  Serial.println((char)val);
}
