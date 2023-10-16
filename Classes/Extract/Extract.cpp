#include <Servo.h>
#include <Arduino.h>
#include "Extract.h"


// Setup
void Extract::setUp(void) {
  Extract::myservo.attach(pinSer);
  Extract::myservo.write(0); 
}

void Extract::set_pos(int pos) {
  Extract::myservo.write(pos);
}

// Get measurement of the servo motor (in degrees)
int Extract::get_pos_analog(void) {
  return Extract::myservo.read();
}
