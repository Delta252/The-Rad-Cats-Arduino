#include <Servo.h>

class Pump{
  private:
    Servo serPump;  
    int pinNum;     // pin number (should be 2 vor the servo)
    //enum pump_type {servo=0, stepper=1}; 
    bool pump_type; // 0 = servo; 1 = stepper
    float flowrate;
    float volume;
    bool dir;
    int Stop; // Stopping value for servo pump
    double conv_ratio;   // conversions of servo (?) to ml
    double steps_per_ml; // Number of steps per ml


    int StepsPerRev;
    int dirStep;            // Pin number for direction - SET TO 5
    int Step;              // Pin number with actual signal - SET TO 2
    int EN;                // Pin number to activate/deactivate - SET TO 8
    float step2ml;


    
  public:
// Constructor and initial settings - variable type_of_pump: 0 = servo, 1 = stepper
    Pump(int pinPump, bool type_of_pump):pinNum(pinPump),pump_type(type_of_pump){}
    Pump(int d, int s, int e, bool type_of_pump):dirStep(d), Step(s), EN(e), pump_type(type_of_pump){}



// Setup
    void setUp(void);


// Set direction and volume of pump
  void set_vol(float vol, bool direc);



// Stop pumping
  void stop_pumping(void);



// Set direction of pumping (no actual pumping); 1 = clockwise; 0 = anticlockwise
  void set_dir(bool Direction);



// Get measurement for direction (0 for into reactor, 1 for reverse)
  bool get_last_dir();



// Get measurement for volume pumped (in ml)
  double get_last_vol();



// Get measurement for flowrate of SERVO (in ml per seconds)
  double get_flow_rate();



// Set type of pump - SERVO = 0; STEPPER = 1
  void set_pump_type(bool type_of_pump);



// Get pump type - SERVO = 0; STEPPER = 1
  bool get_pump_type(void);



// Set convertion ratio for servo pumps (for calibration)
  void set_conv_ratio(double convertion);



// Get convertion ratio (servo)
  double get_conv_ratio(void);


// Set the number of steps per ml in stepper pump (for calibration)
  void set_steps_per_ml(double num_steps);



// Get number of steps per ml (stepper)
  double get_steps_per_ml(void);

}; // End Class Pump


/*int flag=1;
Pump mypump(12,0);
Pump StepPump(5,2,8,1);

void setup(){
  Serial.begin(115200);
  mypump.setUp();
  StepPump.setUp();
}

void loop(){
  if(flag==1){
    StepPump.set_vol(2.5,1);
    mypump.set_vol(2.5,1);
    flag++;
  }   
}*/
