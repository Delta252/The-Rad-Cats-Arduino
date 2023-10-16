#include <Servo.h>
#include <Arduino.h>

class Pump{
  private:
    Servo serPump;  
    int pinNum;     // pin number (should be 2 vor the servo)
    //enum pump_type {servo=0, stepper=1}; 
    bool pump_type; // 0 = servo; 1 = stepper
    float volume = 0;
    bool dir = 0;
    int Stop = 90; // Stopping value for servo pump
    double conv_ratio = 0.0052;   // conversions of servo (?) to ml
    double steps_per_ml = 9271.13 ; // Number of steps per ml


    int StepsPerRev = 3200;
    int dirStep = 5;            // Pin number for direction - SET TO 5
    int Step = 2;              // Pin number with actual signal - SET TO 2
    int EN = 8;                // Pin number to activate/deactivate - SET TO 8
    float step2ml = 9271.13 ;


  public:
  
// Constructor and initial settings - variable type_of_pump: 0 = servo, 1 = stepper
    Pump(int pinPump, bool type_of_pump):pinNum(pinPump),pump_type(type_of_pump){}
    Pump(int d, int s, int e, bool type_of_pump):dirStep(d), Step(s), EN(e), pump_type(type_of_pump){}

// Setup
    void Pump::setUp(void){
      if(pump_type == 0){
        serPump.attach(pinNum);
        serPump.write(Stop);
      }  
      if(pump_type == 1){
        pinMode(dirStep, OUTPUT);
        pinMode(Step, OUTPUT);
        pinMode(EN, OUTPUT);
        digitalWrite(EN, LOW);
      }
    } // End function
    


// Set direction and volume of pump
  void Pump::set_vol(float vol, bool direc){
    Pump::volume = vol;
    Pump::dir = direc;
    
    if(pump_type == 0){ // SERVO
      long pumping_time = abs((2068.7 * (vol+0.6)) - 2288.1);
      if (direc == 1){
        serPump.write(0); //Clockwise maximum speed rotation (0 degrees)
        delay(pumping_time);
      }
      if (direc == 0){
        serPump.write(180); //Anti clockwise maximum speed rotation (0 degrees)
        delay(pumping_time);
      }
      serPump.write(Stop);      
    }// End if servo

    if(pump_type == 1){ // STEPPER
      digitalWrite(dirStep, direc); 
      for (uint32_t i = 0; i < (9261.8*vol)+42.827; i++) {
        digitalWrite(Step, HIGH);
        delay(1);
        digitalWrite(Step, LOW);
        delay(1);
      }
    }// End if stepper
    
  }// End function



// Stop pumping
  void Pump::stop_pumping(void){
    if(pump_type == 0){ // Servo
      serPump.write(Stop);
    }
    if(pump_type == 1){ // Stepper
      digitalWrite(Step, LOW);
    }
  }// End function



// Set direction of pumping (no actual pumping); 1 = clockwise; 0 = anticlockwise
  void Pump::set_dir(bool Direction){
    dir = Direction;
  }



// Get measurement for direction (0 for into reactor, 1 for reverse)
  bool Pump::get_last_dir(){
    return Pump::dir;
  }// End function



// Get measurement for volume pumped (in ml)
  double Pump::get_last_vol(){
    return Pump::volume;
  }// End function




// Set type of pump - SERVO = 0; STEPPER = 1
  void Pump::set_pump_type(bool type_of_pump){
    pump_type = type_of_pump;
  }// End function



// Get pump type - SERVO = 0; STEPPER = 1
  bool Pump::get_pump_type(void){
    return Pump::pump_type;
  }



// Set convertion ratio for servo pumps (for calibration)
  void Pump::set_conv_ratio(double convertion){
    if(pump_type == 0){
      conv_ratio = convertion;
      //?????????????????????????????????????????????????????????????????????????????
      // Is it the constant 0.0052 in set_vol?
    }    
  }// End function



// Get convertion ratio (servo)
  double Pump::get_conv_ratio(void){
    if(pump_type == 0){
      return conv_ratio;
    }
    else return 0;
  }// End function
  


// Set the number of steps per ml in stepper pump (for calibration)
  void Pump::set_steps_per_ml(double num_steps){
    if(pump_type == 1){
      steps_per_ml = num_steps;
    }
  }// End function



// Get number of steps per ml (stepper)
  double Pump::get_steps_per_nl(void){
    if(pump_type == 0){
      return steps_per_ml;
    }
    else return 0;
  }// End function

}; // End Class Pump


/*int flag=1;
Pump ServoPump(12,0);
Pump StepPump(5,2,8,1);

void setup(){
  Serial.begin(115200);
  ServoPump.setUp();
  StepPump.setUp();
}

void loop(){
  if(flag==1){
    //StepPump.set_vol(40,1);
    ServoPump.set_vol(30,1);
    flag++;
    
  }   
  delay(100);
}*/

