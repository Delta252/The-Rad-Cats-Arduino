#include <Arduino.h>

enum method
{
    SINGLE,
    DOUBLE;
}



class StepperMotor
{
    public:
    //Constructor
    StepperMotor(uint16_t revSteps, uint8_t portNumber);
    void run(uint16_t numOfSteps, bool dir, uint8_t method);
    void setSpeed(uint16_t speed);
    uint32_t timePerStep, timer;
}