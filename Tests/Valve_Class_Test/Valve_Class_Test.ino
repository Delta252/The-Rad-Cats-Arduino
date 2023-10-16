#include "Valve_Class.h"

Valve myvalve2(2, 55, 135);

// Servo myservo2;
void setup(){
  myvalve2.setUp();

}

int a=0,b=70;
void loop2(){
  myvalve2.set_pos1();
  delay(500);
  delay(2000);
  myvalve2.set_pos0();
  delay(500);
  delay(2000);
  myvalve2.set_pos(2);
  a = a+10;
  b = b-10;
  myvalve2.set_angle_lims(a,b);
}
