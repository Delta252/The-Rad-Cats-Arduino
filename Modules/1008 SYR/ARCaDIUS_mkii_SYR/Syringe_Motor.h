#include <Arduino.h>
#include "AccelStepper.h"

#define MOTORLATCH 12
#define MOTORCLK 4
#define MOTORENABLE 7
#define MOTORDATA 8

class StepperMotor
{
    private:
    AccelStepper myMotor;
    public:
    //Constructor
    StepperMotor() = default;
    void setUp();
    void pumpVolume(uint16_t volume);
};