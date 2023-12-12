#include "Syringe_Motor.h"

void StepperMotor::setUp(void)
{
  myMotor.setSpeed(200);
  myMotor.moveTo(0);
}

void StepperMotor::pumpVolume(uint16_t volume)
{
  //Will probably need to do some maths once calibrated to calculate volume through distance
  uint16_t distanceToMove = volume;
  myMotor.move(distanceToMove);
}
// void StepperMotor::enable()
// {
//     pinMode(MOTORLATCH, OUTPUT);
//     pinMode(MOTORENABLE, OUTPUT);
//     pinMode(MOTORDATA, OUTPUT);
//     pinMode(MOTORCLK, OUTPUT);

//     pinMode(11, OUTPUT);
//     pinMode(3, OUTPUT);
//     digitalWrite(11, HIGH);
//     digitalWrite(3, HIGH);
// }

// void run(uint16_t numOfSteps, bool dir, uint8_t method)
// {
//     while (numOfSteps--) {
//     ret = onestep(dir, style);
//     delay(uspers/1000); // in ms
//     steppingcounter += (uspers % 1000);
//     if (steppingcounter >= 1000) {
//       delay(1);
//       steppingcounter -= 1000;
//     }
//   }
// }