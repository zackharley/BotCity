// MAC Address: 201505057960

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(Serial.available()==1)
  {
  char c = Serial.read();
  Serial.println(c);
  if(c=='Y')
    Serial.println("Hello World!");
  } 
}
