#include <Servo.h>
#include <Arduino.h>

class Valve {
  private:
    int posOpen = 0;
    int posClose = 1;
    int posMid = 2;
    int a = 0;
    int angleMid = 90;
    int angleOpen = 67;
    int angleClose = 123;
    int pinSer;  // pin number (should be 2 for the servo)
    Servo myservo;



  public:
    // Constructor and initial settings
    Valve(int pinServo, int AngO, int AngC): pinSer(pinServo), angleOpen(AngO), angleClose(AngC) {}



    // Setup
    void setUp() {
      myservo.write(90);
      myservo.attach(Valve::pinSer);
    }


    void set_pos(int pos) {
      if (pos == 0) { // If pos is open
        Valve::a = posOpen;
        myservo.write(angleOpen);
      }
      if (pos == 1) { // If pos is closed
        Valve::a = posClose;
        myservo.write(angleClose);
      }
      if (pos == 2) { // If pos is middle
        Valve::a = posMid;
        myservo.write(angleMid);
      }
    }

    /*

      // Set valve position to 1
        void set_pos1(void){
          Valve::a = posClose;
          myservo.write(angleClose);
        } // End function


      // Set valve position to 0
        void set_pos0(void){
          Valve::a = posClose;
          myservo.write(angleClose);
        } // End function


      // Toggle valve position
        void toggle_pos(void){
          if (get_pos_digital() == 1){
            set_pos0();
          } // End if
          else {
            set_pos1();
          } // End else
        } // End funtion

    */


    // Set the limit position of the servo motor (in degrees)
    void set_angle_lims(int angle0, int angle1) { // Angle0 is for open, Angle1 is for close
      Valve::angleOpen = angle0;
      Valve::angleClose = angle1;
    } // End function



    // Get measurement of the servo motor (in degrees)
    int get_pos_analog(void) {
      return myservo.read();
    }



    // Get state of valve (0 (open), 1 (closed), 2 (middle))
    int get_pos_digital(void) {
      if (a == 0) {
        return 0;  // Open
      } // End if
      if (a == 1) {
        return 1; // Closed
      }// End if
      if (a == 2) {
        return 2; // Middle
      }
    } // End function



    // Get measurement of the limit set for the servo motor (in degrees)
    int get_lim(int pos) {
      if (pos == 0) {
        return Valve::angleOpen;
      }
      if (pos == 1) {
        return Valve::angleClose;
      }
      if (pos == 3) {
        return Valve::angleMid;
      }
    } // End function
};

/*
  Valve myvalve(3,55,125);
  Servo myservo2;

  void setup(){
  myvalve.setUp();
  }

  int a=0,b=80;
  void loop(){
  myvalve.set_pos(0);
  delay(500);
  delay(1000);
   myvalve.set_pos(2);
  delay(500);
  delay(1000);
  myvalve.set_pos(1);
  delay(500);
  delay(1000);
   myvalve.set_pos(2);
  delay(500);
  delay(1000);

  a = a+10;
  b = b-10;
  myvalve.set_angle_lims(a,b);
  myvalve.set_pos(0);
  delay(500);
  delay(2000);
  }
*/
