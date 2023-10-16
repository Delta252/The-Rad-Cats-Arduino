#include "LDSensor.h"

void LDSensor:: setUp() {
  pinMode(Input, INPUT);
}

bool LDSensor:: StatusLDS () {
  return digitalRead(Input);
}
