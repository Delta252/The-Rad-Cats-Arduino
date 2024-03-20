#include <Servo.h>
#include <Arduino.h>
#include "Valve.h"


// Setup
void Valve::setUp(void) {
  Valve::myservo.attach(pinSer);
  Valve::myservo.write(90); 
  delay(500);
  Valve::myservo.write(130);
  delay(500);
  Valve::myservo.write(60);  
}

void Valve::set_pos(int pos) {
  Valve::a=pos;
  switch(pos) {
    case 0:
      Valve::myservo.write(angleOpen);
      break;
    case 1:
      Valve::myservo.write(angleClose);
      break;
    case 2:
      Valve::myservo.write(angleMid);
      break;
    default:
      break;
  }
  Serial.println(pinSer);
  Serial.println(get_pos_analog());
}


// Set the limit position of the servo motor (in degrees)
void Valve::set_angle_lims(int angle0, int angle1) { // Angle0 is for open, Angle1 is for close
  angleOpen = angle0;
  angleClose = angle1;
} // End function



// Get measurement of the servo motor (in degrees)
int Valve::get_pos_analog(void) {
  return Valve::myservo.read();
}



// Get state of valve (0 (open), 1 (closed), 2 (middle))
int Valve::get_pos_digital(void) {
  return Valve::a;
  
} // End function



// Get measurement of the limit set for the servo motor (in degrees)
int Valve::get_lim(int pos) {
  if (pos == 0) {
    return angleOpen;
  }
  if (pos == 1) {
    return angleClose;
  }
  if (pos == 2) {
    return angleMid;
  }
} // End function

void ValveHandler::openValve1()
{
  //Open Valve 1, close other valves
  V1.set_pos(0);
  V2.set_pos(1);
  V3.set_pos(1);
  V4.set_pos(1);
  V5.set_pos(1);
}