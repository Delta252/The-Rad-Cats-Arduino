#include <Arduino.h>
//#include <ServoTimer2.h>
#include <Servo.h>


enum state{
    closed = 120,
    open = 0,
    open2 = 240,
};

class Shutter{
        private: 
        Servo ShutterServo;
        int input_pin, output_pin;

    public:
        Shutter(int inputpin, int outputpin);
        // Constructor
        // @param inputpin: arduino pin connection for the analog feedback
        // @param outputpin: arduino pin connection for control of the servo

        void Initialise();
        //Initialises object, run in arduino setup 

        void goto_open (double desired);
        // Open loop control of servo position
        // @param desired: Desired angle of the shutter in degrees
       

        double get();
        // Returns a double of angle in degrees
       

        void goto_controlled (double desired);
        // Closed loop control of servo position
        // Cpp file may need altering to tune PI controller
        // @param desired: Desired angle of the shutter in degrees

        void moveto(state pos, bool contol);
        //Moves shutter to preset positions
        // @param pos: Desired preset position, edit state above to include different positions
        // @param control: Set 0 to use goto_open, Set 1 to use goto_controlled

        void timedExposure(state pos, unsigned int exposure_time, bool controller);
        // Moves shutter to preset position then returns to original position after a set time has elapsed 
        // @param pos: Desired preset position, edit state above to include different positions
        // @para  exposure_time: Miliseconds  before returning to original position
        // @param controller: Set 0 to use goto_open, Set 1 to use goto_controlled

};