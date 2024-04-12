#include <Arduino.h>
#include "AccelStepper.h"
#include <Servo.h>

//Motor interface type: 1 = Stepper driver
#define MOTOR_INTERFACE_TYPE 1
//Only change step, dir, or enable if the PCB changes the GPIO pins available to these 
#define STEP 8
#define DIR 7
#define ENABLE 4

//Angle defines
#define ANGLE_INPUT 0
#define ANGLE_OUTPUT 80
#define ANGLE_MIDDLE 40

//Syringe type defines
enum SYRINGE_TYPE
{
  PLACEHOLDER,
  CONCENTRIC5ML,
  CONCENTRIC2ML,
  ECCENTRIC10ML,
};

//Syringe calibration defines
#define CONCENTRIC5ML_SYRINGE_VAL 0.0483
#define CONCENTRIC2ML_SYRINGE_VAL 0 //TBD
#define ECCENTRIC10ML_SYRINGE_VAL 0 //TBD

#define INPUT true
#define OUTPUT false


class StepperMotor
{
    private:
    int pinSer;
    int input;
    int output;
    Servo pumpValve;
    public:
    //Constructor
    StepperMotor(int servoPin, int inputAngle, int outputAngle): pinSer(servoPin), input(inputAngle), output(outputAngle){}
    void setUp();
    void pumpVolume(float volume, int syringeType);
    void setValve(bool IO);
    void fullPlunge(float maxStep);
    void emptyPlunge();
    void partialPlunge(float desiredStep);
    void fullFlush();
};