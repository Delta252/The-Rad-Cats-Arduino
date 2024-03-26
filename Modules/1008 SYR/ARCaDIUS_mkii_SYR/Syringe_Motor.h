#include <Arduino.h>
#include "AccelStepper.h"

class StepperMotor
{
    private:
    public:
    //Constructor
    StepperMotor() = default;
    void setUp();
    void pumpVolume(float volume, uint16_t direction);
    void move();
};