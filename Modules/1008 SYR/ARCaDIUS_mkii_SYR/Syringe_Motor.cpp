#include "Syringe_Motor.h"

AccelStepper accelMotor(MOTOR_INTERFACE_TYPE, STEP, DIR);

void StepperMotor::setUp(void)
{
  //Initialise servo
  pumpValve.attach(pinSer);
  pumpValve.write(ANGLE_OUTPUT);
  delay(500);
  pumpValve.write(ANGLE_INPUT); 
  delay(500);
  pumpValve.write(ANGLE_MIDDLE); 

  //Initialise motor acceleration
  accelMotor.setAcceleration(60);


  fullFlush();
}

void StepperMotor::pumpVolume(float volume, int syringeType)
{
  float partialStep = 0;
  float maxStep = 0;
  int maxSyringeVolume = 0;
  int fullSyringePumps = 0;
  int remainderVolume = 0;

  switch(syringeType)
  {
    case(CONCENTRIC5ML):
      //Calculate maximum volume
      maxSyringeVolume = 5;
      //Set max speed, pushback from needle tip requires lower speeds for larger syringes
      accelMotor.setMaxSpeed(CONCENTRIC5ML_SYRINGE_MAX_SPEED);
      accelMotor.setSpeed(CONCENTRIC5ML_SYRINGE_MAX_SPEED);
      //Calculate number of full syringe plunges needed
      fullSyringePumps = volume / maxSyringeVolume;
      //Calculate remainder volume that cannot be pumped by a full plunge
      remainderVolume = volume - (fullSyringePumps * maxSyringeVolume);
      //Calculate the maximum step the syringe supports
      maxStep = (maxSyringeVolume + CONCENTRIC5ML_SYRINGE_VAL_CONSTANT) / CONCENTRIC5ML_SYRINGE_VAL_DIVISOR;
      //Calculate the step needed to pump a partial volume
      partialStep = maxStep - (remainderVolume + CONCENTRIC5ML_SYRINGE_VAL_CONSTANT) / CONCENTRIC5ML_SYRINGE_VAL_DIVISOR;
      break;
    //See comments above for explanation
    case(CONCENTRIC2ML):
      maxSyringeVolume = 2;
      accelMotor.setMaxSpeed(CONCENTRIC2ML_SYRINGE_MAX_SPEED);
      accelMotor.setSpeed(CONCENTRIC2ML_SYRINGE_MAX_SPEED);
      fullSyringePumps = volume / maxSyringeVolume;
      remainderVolume = volume - (fullSyringePumps * maxSyringeVolume);
      maxStep = (maxSyringeVolume + CONCENTRIC2ML_SYRINGE_VAL_CONSTANT) / CONCENTRIC2ML_SYRINGE_VAL_DIVISOR;
      partialStep = maxStep - (remainderVolume + CONCENTRIC2ML_SYRINGE_VAL_CONSTANT) / CONCENTRIC2ML_SYRINGE_VAL_DIVISOR;
      break;
    case(ECCENTRIC10ML):
      maxSyringeVolume = 10;
      accelMotor.setMaxSpeed(ECCENTRIC10ML_SYRINGE_MAX_SPEED);
      accelMotor.setSpeed(ECCENTRIC10ML_SYRINGE_MAX_SPEED);
      fullSyringePumps = volume / maxSyringeVolume;
      remainderVolume = volume - (fullSyringePumps * maxSyringeVolume);
      maxStep = (maxSyringeVolume + ECCENTRIC10ML_SYRINGE_VAL_CONSTANT) / ECCENTRIC10ML_SYRINGE_VAL_DIVISOR;
      partialStep = maxStep - (remainderVolume + ECCENTRIC10ML_SYRINGE_VAL_CONSTANT) / ECCENTRIC10ML_SYRINGE_VAL_DIVISOR;
      break;
    default:
      Serial.println("Unsupported Syringe Type.");
      partialStep = 0;
      break;
  }

  //Repeat full syringe pumps for number of times required
  for(int i = 0; i < fullSyringePumps; i++)
  {
    fullPlunge(maxStep);
    emptyPlunge();
  }

  //Refill syringe before pumping out remainder volume (if any)
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
  if(IO == INPUT)
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
  //Switch valve to input
  setValve(INPUT);
  delay(500);
  //Move to maximum step
  accelMotor.moveTo(maxStep);

  //While the actuator is not at its destination, move the motor
  while(accelMotor.distanceToGo() != 0)
  {
    accelMotor.run();
  }
}

void StepperMotor::emptyPlunge()
{
  //Set valve to output
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
  //Set valve to output
  setValve(OUTPUT);
  delay(500);
  accelMotor.moveTo(desiredStep);

  while(accelMotor.distanceToGo() != 0)
  {
    accelMotor.run();
  }
}

/*
  fullFlush():
  Move the actuator to a guaranteed minimum point, then set that point as 0.
*/
void StepperMotor::fullFlush()
{
  //Flush into the input
  setValve(INPUT);
  delay(500);
  accelMotor.moveTo(-6000);

  while(accelMotor.distanceToGo() != 0)
  {
    accelMotor.run();
  }

  //Reset current position to 0
  accelMotor.setCurrentPosition(0);
}