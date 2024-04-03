#include "Syringe_Motor.h"

//Able to compile with both Nano Every and Uno boards with the HW130 Motor Shield.
#ifdef ARDUINO_NANO_EVERY
  #define BOARD "NanoEvery"
  AccelStepper accelMotor(MOTOR_INTERFACE_TYPE, STEP, DIR);
#endif

//Uno boards with HW130 motor shield uses AFMotor library.
#ifdef ARDUINO_AVR_UNO
  #define BOARD "Uno"
  #include "AFMotor.h"
  AF_Stepper motor(200, 1);

  //Define forward step and backward step for constructor
  void forwardstep()
  {
    motor.onestep(FORWARD, SINGLE);
  }

  void backwardstep()
  {
    motor.onestep(BACKWARD, SINGLE);
  }

  //Use custom AccelStepper constructor for use with motor shield (See AccelStepper documentation for more information)
  AccelStepper accelMotor(forwardstep, backwardstep);
#endif

void StepperMotor::setUp(void)
{
  Serial.println(BOARD);

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