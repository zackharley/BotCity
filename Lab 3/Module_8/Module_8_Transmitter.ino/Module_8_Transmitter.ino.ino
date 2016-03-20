#include <QSerial.h>
QSerial IRserial;

void setup() {
  // put your setup code here, to run once:
 pinMode(3,OUTPUT);
 IRserial.attach(-1,3);
}

void loop() {
  // put your main code here, to run repeatedly:
  IRserial.transmit('Y');
  IRserial.transmit('E');
  IRserial.transmit('S');
  IRserial.transmit('!');
  delay(100);
}
