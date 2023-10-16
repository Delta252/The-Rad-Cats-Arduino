#ifndef LDS_h
#define LDS_h

#include <Arduino.h>

class LDS 
{

  private: 
  int Liquid_level = 0;
  int pin = 6;

  public:
  LDS() {}

  void SetUpLDS() {
    Serial.begin(9600);
    pinMode(pin,INPUT);
    }  
 

  bool LiquidDetected () {
    Liquid_level=digitalRead(pin); 
    if (Liquid_level == HIGH) { 
      return true;
    }
    else {
      return false; 
    }
  }
};
#endif