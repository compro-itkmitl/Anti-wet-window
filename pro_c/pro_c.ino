int statPin = 4; 
int comPin = 5;
int modePin = 6;
int swtPin = 7;
int speakPin = 12;

void setup() {
  // put your setup code here, to run once:
  pinMode(statPin, OUTPUT);
  pinMode(modePin, INPUT);
  pinMode(swtPin, INPUT);
  pinMode(comPin, INPUT);
  pinMode(motorPin1, OUTPUT);
  pinMode(motorPin2, OUTPUT);
  pinMode(motorPin3, OUTPUT);
  pinMode(motorPin4, OUTPUT);
  pinMode(speakPin, OUTPUT);
  digitalWrite(statPin, LOW);
}

void loop() {
  // put your main code here, to run repeatedly:
  int rain_value = analogRead(A0);
  int swt = digitalRead(swtPin);
  int mode = digitalRead(modePin);
  int com = digitalRead(comPin);
  if(mode==0){
    if(rain_value<=500){
      if(swt==1){
        for(int i=0;i<400;i++){
          motor();
          digitalWrite(speakPin, HIGH);
        }
        digitalWrite(speakPin, LOW);
      }
    }
  }
  
  else if(mode==1){
    if(com==1&&swt==1){
      for(int i=0;i<400;i++){
          motor();
          digitalWrite(speakPin, HIGH);
        }
      digitalWrite(statPin, HIGH);
      delay(300);
      digitalWrite(statPin, LOW);
    }
    else if(com==1&&swt==0){
      for(int i=0;i<400;i++){
        motor_re();
      }
      digitalWrite(statPin, HIGH);
      delay(300);
      digitalWrite(statPin, LOW);
    }
  }
}
