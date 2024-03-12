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
  accelMotor.setMaxSpeed(100);
  accelMotor.setSpeed(100);
  accelMotor.setAcceleration(100);
}

//bool dir = true means forward, dir = false means backwards.
void StepperMotor::pumpVolume(float volume, uint16_t direction)
{
  //Will probably need to do some maths once calibrated to calculate volume through distance
  float distanceToMove = volume;
  // if(volume != 0)
  // {
  //   distanceToMove = (volume / 0.01964) * 20;
  // }
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