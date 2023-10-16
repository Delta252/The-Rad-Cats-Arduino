#include "LDSensor.h"

void LDSensor:: setUp() {
  pinMode(Input, INPUT);
}

bool LDSensor:: StatusLDS () {
  Liquid_level = digitalRead(Input);
  if (Liquid_level == HIGH) {
    return true;
  }
  else {
    return false;
  }
}
