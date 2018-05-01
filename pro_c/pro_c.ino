int statPin = 4;
int comPin = 5;
int modePin = 6;
int swtPin = 7;
int motorPin1 = 8;  //StepMotor_28BYJ48 pin 1
int motorPin2 = 9;  //StepMotor_28BYJ48 pin 2
int motorPin3 = 10; //StepMotor_28BYJ48 pin 3
int motorPin4 = 11; //StepMotor_28BYJ48 pin 4
int speakPin = 12;
int motorSpeed = 4;

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
  Serial.begin(115200);
  digitalWrite(statPin, LOW);
}

void loop() {
  // put your main code here, to run repeatedly:
  int rain_value = analogRead(A0);
  int swt = digitalRead(swtPin);
  int mode = digitalRead(modePin);
  int com = digitalRead(comPin);

  Serial.print("rain_value = ");
  Serial.println(rain_value);
  Serial.print("swt = ");
  Serial.println(swt);
  Serial.print("mode = ");
  Serial.println(mode);
  Serial.print("com = ");
  Serial.println(com);
  Serial.println("===============");

  if (mode == 0) {
    if (rain_value <= 500) {
      if (swt == 1) {
        while (swt == 1) {
          swt = digitalRead(swtPin);
          motor();
          digitalWrite(speakPin, HIGH);
        }
        digitalWrite(speakPin, LOW);
      }
    }
  }

  else if (mode == 1) {
    if (com == 1 && swt == 1) {
      while (swt == 1) {
        Serial.println("Closing");
        swt = digitalRead(swtPin);
        motor();
      }
      digitalWrite(statPin, HIGH);
      delay(300);
      digitalWrite(statPin, LOW);
    }
    else if (com == 1 && swt == 0) {

      for (int i = 0; i < 850; i++) {
        Serial.println("Opening");
        motor_re();
      }
      digitalWrite(statPin, HIGH);
      delay(300);
      digitalWrite(statPin, LOW);
    }
  }
}

void motor_re() {
  //StepMotor_Working_Step
  //Step_1
  digitalWrite(motorPin1, LOW);
  digitalWrite(motorPin2, LOW);
  digitalWrite(motorPin3, LOW);
  digitalWrite(motorPin4, HIGH);
  delay(motorSpeed);
  //Step_2
  digitalWrite(motorPin1, LOW);
  digitalWrite(motorPin2, LOW);
  digitalWrite(motorPin3, HIGH);
  digitalWrite(motorPin4, HIGH);
  delay (motorSpeed);
  //Step_3
  digitalWrite(motorPin1, LOW);
  digitalWrite(motorPin2, HIGH);
  digitalWrite(motorPin3, LOW);
  digitalWrite(motorPin4, LOW);
  delay(motorSpeed);
  //Step_4
  digitalWrite(motorPin1, HIGH);
  digitalWrite(motorPin2, LOW);
  digitalWrite(motorPin3, LOW);
  digitalWrite(motorPin4, LOW);
  delay(motorSpeed);
}

void motor() {
  //StepMotor_Working_Step
  //Step_4
  digitalWrite(motorPin1, HIGH);
  digitalWrite(motorPin2, LOW);
  digitalWrite(motorPin3, LOW);
  digitalWrite(motorPin4, LOW);
  delay(motorSpeed);
  //Step_3
  digitalWrite(motorPin1, LOW);
  digitalWrite(motorPin2, HIGH);
  digitalWrite(motorPin3, LOW);
  digitalWrite(motorPin4, LOW);
  delay(motorSpeed);
  //Step_2
  digitalWrite(motorPin1, LOW);
  digitalWrite(motorPin2, LOW);
  digitalWrite(motorPin3, HIGH);
  digitalWrite(motorPin4, HIGH);
  delay (motorSpeed);
  //Step_1
  digitalWrite(motorPin1, LOW);
  digitalWrite(motorPin2, LOW);
  digitalWrite(motorPin3, LOW);
  digitalWrite(motorPin4, HIGH);
  delay(motorSpeed);
}
