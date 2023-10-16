#ifndef BubbleSensor_h
#define BubbleSensor_h

#include <Arduino.h>

class BubbleSensor 
{

  private: 
  int Input;
  int Output;

  public:
  float average;
  BubbleSensor(int in, int out) {Input = in; Output = out;};
  // Constructor with 2 inputs which connect to the pins

  void setupBS();
  // Sets up the Bubble sensor (to be used in void setup())

  int Status();
  // Reads the sensor
  // Returns 1 when there is tube but no luquid, 2 when there is tube and liquid, 3 when there is no tube
};
  #endif
