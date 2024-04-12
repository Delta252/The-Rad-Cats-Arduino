#include "Syringe_Motor.h"

AccelStepper accelMotor(MOTOR_INTERFACE_TYPE, STEP, DIR);

void StepperMotor::setUp(void)
{
  pumpValve.attach(pinSer);
  pumpValve.write(ANGLE_OUTPUT);
  delay(500);
  pumpValve.write(ANGLE_INPUT); 
  delay(500);
  pumpValve.write(ANGLE_MIDDLE); 
  //Initialise parameters regarding speed
  accelMotor.setMaxSpeed(200);
  accelMotor.setSpeed(200);
  accelMotor.setAcceleration(200);
}

void StepperMotor::pumpVolume(float volume)
{
  float desiredStep = 0;
  //Calculate distance needed to move
  desiredStep = (volume + 0.0483) / 0.0011;
  if(volume > 0)
  {
    //Equation relating motor step and volume
    pumpValve.write(ANGLE_INPUT);
  Serial.println("INPUT");
  }
  else if(volume < 0)
  {
    pumpValve.write(ANGLE_OUTPUT);
  Serial.println("OUTPUT");
  }
  else
  {
    pumpValve.write(ANGLE_OUTPUT);
  Serial.println("DRAIN");
    desiredStep = 0;
  }
  //Set the desired step
  Serial.println("Distance to move:" + (String)desiredStep);
  accelMotor.moveTo(desiredStep);

  while(accelMotor.distanceToGo() != 0)
  {
    accelMotor.run();
  }
}
  //Run the motor until desiredStep is reached
void StepperMotor::setValve(int pos)
{

}