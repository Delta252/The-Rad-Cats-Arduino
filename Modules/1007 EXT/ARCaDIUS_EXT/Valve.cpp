#include <Servo.h>
#include <Arduino.h>
#include "Valve.h"


// Setup
void Valve::setUp(void) {
  myservo.attach(pinSer);
  myservo.write(90);
}

void Valve::set_pos(int pos) {
  a=pos;
  if (pos == 0) { // If pos is open
    myservo.write(angleOpen);
  }
  else if (pos == 1) { // If pos is closed
    myservo.write(angleClose);
  }
  else if (pos == 2) { // If pos is middle
    myservo.write(angleMid);
  }
  
}


// Set the limit position of the servo motor (in degrees)
void Valve::set_angle_lims(int angle0, int angle1) { // Angle0 is for open, Angle1 is for close
  angleOpen = angle0;
  angleClose = angle1;
} // End function



// Get measurement of the servo motor (in degrees)
int Valve::get_pos_analog(void) {
  return myservo.read();
}



// Get state of valve (0 (open), 1 (closed), 2 (middle))
int Valve::get_pos_digital(void) {
  return a;
  
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

