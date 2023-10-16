#ifndef LDSensor_h
#define LDSensor_h

#include <Arduino.h>

class LDSensor 
{

  private: 
  int Liquid_level = 0;
  int Input;

  public:
  LDSensor(int in) {Input = in;};
  // Constructor, takes one input represnting the pin number

  void SetUpLDS(); 
  // Setup, to be used in void setup() 

  bool StatusLDS();
  // Reads the value of the sensor as a boolean value
  // Returns 1 if there is liquid and 0 if there isn't
};
#endif
