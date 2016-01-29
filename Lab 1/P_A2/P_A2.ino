#define pushButton 12
#define redLED 11
#define yellowLED 10

int redFlag = 1;
int yellowFlag = 0;

void setup() {
  // put your setup code here, to run once:
  pinMode(yellowLED,OUTPUT);
  pinMode(redLED,OUTPUT);
  digitalWrite(redLED, HIGH);
}

void loop() {
  while(digitalRead(12));
  while(!digitalRead(12));
  
  if(redFlag){
    redFlag = 0;
    yellowFlag = 1;
  }
  else{
    redFlag = 1;
    yellowFlag = 0;
  }
  digitalWrite(redLED, redFlag);
  digitalWrite(yellowLED, yellowFlag);
}
