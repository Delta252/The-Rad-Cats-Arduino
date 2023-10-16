#ifndef Extract_H
#define Extract_H
#include <Servo.h>

class Extract{
  private:
    int pinSer;  // pin number (should be 2 for the servo)
    Servo myservo;
    
  public:
// Constructor and initial settings
    Extract(int pinServo): pinSer(pinServo){}

// Setup
    void setUp();

// Set Extract position to int 0 to 180
    void set_pos(int pos);

    
// Get measurement of the servo motor (in degrees)
    int get_pos_analog(void);
};

#endif
