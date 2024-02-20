#include <Servo.h>
#import <Arduino.h>
#include "Pump_Class.h"


int flag2=1;
Pump ServoPump2(11,0);
Pump StepPump2(11,2,8,1);

void setup2(){
  Serial.begin(115200);
  ServoPump2.setUp();
  StepPump2.setUp();
  loop2();
}

void loop2(){
  if(flag2==1){
    StepPump2.set_vol(2.5,1);
    ServoPump2.set_vol(2.5,1);
    flag2++;
  }   
}

