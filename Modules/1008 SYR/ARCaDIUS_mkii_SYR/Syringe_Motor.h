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
    
    public:
    //Constructor
    StepperMotor() = default;
    void setUp();
    void pumpVolume(uint16_t volume, uint16_t direction);
    void move();
};