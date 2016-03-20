#include <QSerial.h>
QSerial IRserial;
char trans = '1';
void setup() {
  // put your setup code here, to run once:
 pinMode(3,OUTPUT);
 IRserial.attach(-1,3);
 Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(Serial.available()==1)
    trans = Serial.read();
  Serial.print("Transmitting: ");
  Serial.println(trans);
  IRserial.transmit(trans);
  delay(100);
}
