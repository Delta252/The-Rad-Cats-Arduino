#include <Arduino.h>
#include "AccelStepper.h"


//Motor interface type: 1 = Stepper driver
#define MOTOR_INTERFACE_TYPE 1
//Only change step, dir, or enable if the PCB changes the GPIO pins available to these 
#define STEP 8
#define DIR 7
#define ENABLE 4


class StepperMotor
{
    private:
<<<<<<< Updated upstream
=======
    int pinSer;
    int input;
    int output;
>>>>>>> Stashed changes
    public:
    //Constructor
    StepperMotor(int servoPin, int inputAngle, int outputAngle): pinSer(servoPin), input(inputAngle), output(outputAngle);
    void setUp();
<<<<<<< Updated upstream
    void pumpVolume(float volume);
    void move();
=======
    void pumpVolume(float volume, uint16_t direction);
    void setValve(int pos);
>>>>>>> Stashed changes
};