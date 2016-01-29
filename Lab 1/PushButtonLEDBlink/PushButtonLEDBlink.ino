#define LEDPIN 13
void setup() {
  // put your setup code here, to run once:
  pinMode(LEDPIN,OUTPUT);
  pinMode(12,INPUT);
  while(digitalRead(12));
  while(!digitalRead(12));
}

void loop() {
  digitalWrite(LEDPIN,HIGH);
  delay(1000);
  digitalWrite(LEDPIN,LOW);
  delay(1000);

}
