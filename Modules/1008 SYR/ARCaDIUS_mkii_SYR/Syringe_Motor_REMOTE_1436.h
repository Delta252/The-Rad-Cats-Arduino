#include <Arduino.h>
#include "AccelStepper.h"
#include <AFMotor.h>

#define MOTORLATCH 12
#define MOTORCLK 4
#define MOTORENABLE 7
#define MOTORDATA 8

class StepperMotor
{
    private:
    int pinSer;
    int input;
    int output;
    public:
    //Constructor
    StepperMotor(int servoPin, int inputAngle, int outputAngle): pinSer(servoPin), input(inputAngle), output(outputAngle);
    void setUp();
    void pumpVolume(float volume, uint16_t direction);
    void setValve(int pos);
};