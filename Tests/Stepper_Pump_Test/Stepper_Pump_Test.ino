int StepsPerRev = 3200;
int dir = 11;
int Step = 2;
int EN = 8;
float step2ml = 1648.8;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(dir, OUTPUT);
  pinMode(Step, OUTPUT);
  pinMode(EN, OUTPUT);
  digitalWrite(dir, HIGH);
  digitalWrite(EN, LOW);
  //  for (int i = 0; i < 3200; i++) {
  //    digitalWrite(Step, HIGH);
  //    delay(1);
  //    digitalWrite(Step, LOW);
  //    delay(1);
  //
  //  }
  digitalWrite(dir, HIGH);
  loop();
}

void loop() {
  // put your main code here, to run repeatedly:
  int BS = analogRead(A0);
  if (Serial.available() > 0) {
    int request = Serial.readStringUntil(',').toInt();
    uint32_t mls = Serial.readStringUntil('\n').toInt();

    //Serial.println(mls);
    for (uint32_t i = 0; i < mls * step2ml; i++) {
      digitalWrite(Step, HIGH);
      delay(1);
      digitalWrite(Step, LOW);
      delay(1);
    }
  }


  delay(100);

}
