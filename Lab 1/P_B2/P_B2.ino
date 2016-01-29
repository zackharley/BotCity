
#define pushButton 10
#define beatz 13
#define yellowLED 12
#define analogPin 0

int singFlag = 1;
int raveFlag = 0;
int val = 0;
void setup() {
  // put your setup code here, to run once:
  pinMode(yellowLED,OUTPUT);
  pinMode(beatz,OUTPUT);
  digitalWrite(beatz, HIGH);
}

void loop() {
  if(!digitalRead(pushButton)){
    if(singFlag){
      singFlag = 0;
      raveFlag = 1;
    }
    else{
      singFlag = 1;
      raveFlag = 0;
    }
    while(!digitalRead(pushButton));
  }
  
  val = analogRead(analogPin);
  if(raveFlag){
    digitalWrite(yellowLED, raveFlag);
    delay(val);
    digitalWrite(yellowLED, LOW);
    delay(val);
  }
  if(singFlag)
    tone(beatz,val,200);
}
