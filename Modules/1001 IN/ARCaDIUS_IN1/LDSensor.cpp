#include "LDSensor.h"

void LDSensor:: setUp() {
  pinMode(Input, INPUT);
}

bool LDSensor:: StatusLDS () {
  Serial.println(digitalRead(Input));
  return digitalRead(Input);
}
