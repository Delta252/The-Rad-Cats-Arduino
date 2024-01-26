#include "Syringe_Motor.h"

AF_Stepper motor(200, 1);

void forwardstep()
{
  motor.onestep(FORWARD, SINGLE);
}

void backwardstep()
{
  motor.onestep(BACKWARD, SINGLE);
}

AccelStepper accelMotor(forwardstep, backwardstep);

void StepperMotor::setUp(void)
{
  accelMotor.setMaxSpeed(200);
  accelMotor.setSpeed(200);
  accelMotor.setAcceleration(50);
}

void StepperMotor::pumpVolume(uint16_t volume)
{
  //Will probably need to do some maths once calibrated to calculate volume through distance
  long distanceToMove = volume;
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