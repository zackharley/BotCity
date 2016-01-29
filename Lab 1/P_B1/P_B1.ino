#define analogPin 0
#define LEDpin 12
int val = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(LEDpin, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  val = analogRead(analogPin);
  Serial.println(val);

  digitalWrite(LEDpin,HIGH);
  delay(val);
  digitalWrite(LEDpin,LOW);
  delay(val);
}
