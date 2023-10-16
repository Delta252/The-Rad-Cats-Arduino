#include "LDS.h"
#include "MixerMotor.h"

LDS LDSSensor1;
MixerMotor MagMix;

void setup() {
  // put your setup code here, to run once:

}


void loop() {
  MagMix.MotorMedium();
  bool state = LDSSensor1.LiquidDetected();
  if (state == true){
    MagMix.StopMotor();
  }

}
