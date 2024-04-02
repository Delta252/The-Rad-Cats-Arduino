#include "Syringe_Motor.h"

AccelStepper accelMotor(MOTOR_INTERFACE_TYPE, STEP, DIR);

void StepperMotor::setUp(void)
{
  //Set enable pin to high
  accelMotor.setPinsInverted(false, false, true);
  accelMotor.setEnablePin(ENABLE);
  //Initialise parameters regarding speed
  accelMotor.setMaxSpeed(200);
  accelMotor.setSpeed(200);
  accelMotor.setAcceleration(200);
}

void StepperMotor::pumpVolume(float volume)
{
  float desiredStep = 0;
  //Calculate distance needed to move
  if(volume != 0)
  {
    //Equation relating motor step and volume
    desiredStep = (volume + 0.0483) / 0.0011;
  }
  //Set the desired step
  Serial.println("Distance to move:" + (String)desiredStep);
  accelMotor.moveTo(desiredStep);

  //Run the motor until desiredStep is reached
  while(accelMotor.distanceToGo() != 0)
  {
    accelMotor.run();
  }
}