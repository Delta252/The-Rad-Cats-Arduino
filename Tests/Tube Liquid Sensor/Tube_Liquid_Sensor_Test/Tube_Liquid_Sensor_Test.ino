#include "BubbleSensor.h"
BubbleSensor Bubble(A0,6);
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Bubble.setupBS();
}

void loop() {
  // put your main code here, to run repeatedly:
  Bubble.Status();
  delay(300);
}
