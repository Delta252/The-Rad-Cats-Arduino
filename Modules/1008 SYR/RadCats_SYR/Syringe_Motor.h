#include <Arduino.h>
#include "AccelStepper.h"
#include <Servo.h>

//Motor interface type: 1 = Stepper driver
#define MOTOR_INTERFACE_TYPE 1
//Only change step, dir, or enable if the PCB changes the GPIO pins available to these 
#define STEP 3
#define DIR 4
#define ENABLE 2

//Angle defines for servo motor
#define ANGLE_INPUT 0
#define ANGLE_OUTPUT 70
#define ANGLE_MIDDLE 40

#define NO_LIQUID 1
#define TUBING_FULL 2

//Syringe type defines
enum SYRINGE_TYPE
{
  PLACEHOLDER,
  CONCENTRIC5ML,
  CONCENTRIC2ML,
  ECCENTRIC10ML,
};

//Syringe calibration defines
#define CONCENTRIC5ML_SYRINGE_VAL_CONSTANT 0.0188
#define CONCENTRIC2ML_SYRINGE_VAL_CONSTANT 0
#define ECCENTRIC10ML_SYRINGE_VAL_CONSTANT 0.08

#define CONCENTRIC5ML_SYRINGE_VAL_DIVISOR 0.011
#define CONCENTRIC2ML_SYRINGE_VAL_DIVISOR 1 //Uncalibrated
#define ECCENTRIC10ML_SYRINGE_VAL_DIVISOR 0.0017

#define CONCENTRIC5ML_SYRINGE_MAX_SPEED 120
#define CONCENTRIC2ML_SYRINGE_MAX_SPEED 0 //Uncalibrated
#define ECCENTRIC10ML_SYRINGE_MAX_SPEED 60

//Input/Output
#define INPUT true
#define OUTPUT false


class StepperMotor
{
    private:
    int pinSer;
    Servo pumpValve;
    public:
    //Constructor, pass through the pin the servo is connected to
    StepperMotor(int servoPin): pinSer(servoPin){}
    void setUp();
    void pumpVolume(float volume, int syringeType);
    void setValve(bool IO);
    void fillSyringe(float maxStep);
    void emptyPlunge();
    void partialPlunge(float desiredStep);
    void fullFlush();
    void startPriming(float maxStep);
};