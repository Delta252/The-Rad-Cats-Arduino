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


  fullFlush();
}

void StepperMotor::pumpVolume(float volume, int syringeType)
{
  float partialStep = 0;
  float maxStep = 0;
  int maxSyringeVolume = 0;
  int fullSyringePumps = 0;
  int remainderVolume = 0;

  //Calculate distance needed to move
  switch(syringeType)
  {
    case(CONCENTRIC5ML):
      maxSyringeVolume = 5;
      fullSyringePumps = volume / maxSyringeVolume;
      remainderVolume = volume - (fullSyringePumps * maxSyringeVolume);
      maxStep = (maxSyringeVolume + CONCENTRIC5ML_SYRINGE_VAL) / 0.0011;
      partialStep = maxStep - (remainderVolume + CONCENTRIC5ML_SYRINGE_VAL) / 0.0011;
      break;
    case(CONCENTRIC2ML):
      maxSyringeVolume = 2;
      fullSyringePumps = volume / maxSyringeVolume;
      remainderVolume = volume - (fullSyringePumps * maxSyringeVolume);
      maxStep = (maxSyringeVolume + CONCENTRIC2ML_SYRINGE_VAL) / 0.0011;
      partialStep = maxStep - (remainderVolume + CONCENTRIC2ML_SYRINGE_VAL) / 0.0011;
      break;
    case(ECCENTRIC10ML):
      maxSyringeVolume = 10;
      fullSyringePumps = volume / maxSyringeVolume;
      remainderVolume = volume - (fullSyringePumps * maxSyringeVolume);
      maxStep = (maxSyringeVolume + ECCENTRIC10ML_SYRINGE_VAL) / 0.0011;
      partialStep = maxStep - (remainderVolume + ECCENTRIC10ML_SYRINGE_VAL) / 0.0011;
      break;
    default:
      Serial.println("Unsupported Syringe Type.");
      partialStep = 0;
      break;
  }
  Serial.println("Full Syringe Pumps: " + (String)fullSyringePumps);
  Serial.println("Partial Syringe Pump: " + (String)remainderVolume);
  for(int i = 0; i < fullSyringePumps; i++)
  {
    fullPlunge(maxStep);
    emptyPlunge();
    Serial.println("One full pump");
  }

  fullPlunge(maxStep);
  partialPlunge(partialStep);
}

/*
  setValve(bool IO)
  
  Sets valve to either input or output depending on parameter passed in.
  When IO = true, set valve to input.
  When IO = false, set valve to output.
*/
void StepperMotor::setValve(bool IO)
{
  if(IO)
  {
    pumpValve.write(ANGLE_INPUT);
  }
  else
  {
    pumpValve.write(ANGLE_OUTPUT);
  }
}

void StepperMotor::fullPlunge(float maxStep)
{
  //Set the desired step
  Serial.println("Distance to move:" + (String)maxStep);
  setValve(INPUT);
  delay(500);
  accelMotor.moveTo(maxStep);

  while(accelMotor.distanceToGo() != 0)
  {
    accelMotor.run();
  }
}

void StepperMotor::emptyPlunge()
{
  //Set the desired step
  setValve(OUTPUT);
  delay(500);
  accelMotor.moveTo(0);

  while(accelMotor.distanceToGo() != 0)
  {
    accelMotor.run();
  }
}

void StepperMotor::partialPlunge(float desiredStep)
{
  //Set the desired step
  setValve(OUTPUT);
  delay(500);
  accelMotor.moveTo(desiredStep);

  while(accelMotor.distanceToGo() != 0)
  {
    accelMotor.run();
  }
}

void StepperMotor::fullFlush()
{
  setValve(INPUT);
  delay(500);
  accelMotor.moveTo(-10000);

  while(accelMotor.distanceToGo() != 0)
  {
    accelMotor.run();
  }

  accelMotor.setCurrentPosition(0);
  Serial.println("Current Position: " + (String)accelMotor.currentPosition());
}