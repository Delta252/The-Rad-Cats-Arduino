#ifndef MixerMotor_h
#define MixerMotor_h
#include <Arduino.h>

class MixerMotor 
{
  private: 
  int MP1;
  int MP2;
  int E;

  public:
  
  MixerMotor(int motorPin1, int motorPin2, int Enable) {MP1 = motorPin1; MP2 = motorPin2; E = Enable;};
  //Constructor
  //@param motorPin1: Motor control PCB connection 1
  //@param motorpin2: Motor control PCB connection 2
  //@param Enable:    Enable pin of control PCB


  void SetUpMotor();
  //Function to be called in setup function of arduino code, Initialises motor pins

  void StopMotor();
  //Stops the motor

  void SetSpeed(int PWM);
  //Sets motor duty cycle
  //@param PWM: Duty cycle as an integer between 0-100

};
#endif

