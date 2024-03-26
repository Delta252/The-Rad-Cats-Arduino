#include "Syringe_Motor.h"

AccelStepper accelMotor(1, 8, 7);

void StepperMotor::setUp(void)
{
  accelMotor.setEnablePin(4);
  accelMotor.setMaxSpeed(200);
  accelMotor.setSpeed(200);
  accelMotor.setAcceleration(200);
}

void StepperMotor::pumpVolume(float volume)
{
  //Will probably need to do some maths once calibrated to calculate volume through distance
  float distanceToMove = volume;
  if(volume != 0)
  {
    distanceToMove = (volume + 0.0483) / 0.0011;
  }
  Serial.println(distanceToMove);
  accelMotor.moveTo(distanceToMove);

  while(accelMotor.distanceToGo() != 0)
  {
    accelMotor.run();
  }
}


void StepperMotor::move()
{
  accelMotor.run();
}