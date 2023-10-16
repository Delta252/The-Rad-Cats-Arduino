#include "Pump.h"
#include "Servo.h"
#include "ARCaDIUS_Serial.h"

// Setup
void Pump::setUp(void) {
  if (pump_type == 0) {
    serPump.attach(pinNum);
    serPump.write(Stop);
  }
  if (pump_type == 1) {
    pinMode(dirStep, OUTPUT);
    pinMode(Step, OUTPUT);
    pinMode(EN, OUTPUT);
    digitalWrite(EN, LOW);
  }
} // End function



// Set direction and volume of pump
void Pump::set_vol(float vol, bool direc) {
  volume = abs(vol);
  dir = direc;
  Serial.println(volume);
  if (pump_type == 0) { // SERVO
    float mlpersec = (0.0038 * volume) + 0.5967;
    uint32_t pumping_time = (volume / mlpersec) * 1000;
    Serial.println(mlpersec);
    Serial.println(pumping_time);
    flowrate = mlpersec;
    if (direc == 1) {
      serPump.write(550); //Clockwise maximum speed rotation (0 degrees)
      delay(pumping_time);
    }
    if (direc == 0) {
      serPump.write(2500); //Anti clockwise maximum speed rotation (0 degrees)
      delay(pumping_time);
    }
    serPump.write(Stop);
  }// End if servo

  if (pump_type == 1) { // STEPPER
    digitalWrite(dirStep, direc);
    for (uint32_t i = 0; i < (vol * steps_per_ml)-38.931; i++) {
      digitalWrite(Step, HIGH);
      delay(1);
      digitalWrite(Step, LOW);
      delay(1);
    }
  }// End if stepper

}// End function



// Pump liquid with feedback from the bubble sensor (Only works for stepper for now)
void Pump::pump_bubble(float vol, bool direc, BubbleSensor B, ASerial Device) {
  volume = abs(vol);
  dir = direc;
  Serial.println(volume);
  if (pump_type == 1) { // STEPPER
    Serial.println("This is a servo Pump");
    digitalWrite(dirStep, direc);
    for (uint32_t i = 0; i < (vol + 0.0155 * vol - 0.0026)*steps_per_ml; i++) {
      digitalWrite(Step, HIGH);
      delay(1);
      digitalWrite(Step, LOW);
      delay(1);
      //if(Pump::B.Status()!=2){
      if (B.Status() != 2) {
        i--;
      }
    }
  }// End if stepper

  if (pump_type == 0) { // SERVO
    float mlpersec = (0.0038 * volume) + 0.5967;
    uint32_t pumping_time = abs((2068.7 * (vol + 0.5)) - 2288.1);
    Serial.println("This is a servo Pump");
    Serial.println(pumping_time);
    flowrate = mlpersec;
    long time1 = 0;
    long time2 = 0;
    long time3 = 0;
    if (direc == 0) {
      serPump.write(2500); //Clockwise maximum speed rotation (0 degrees)
      while ((millis() - time1) < pumping_time) {
        time2 = millis();
        while (B.Status() != 2) {
        }
        time3 = millis();
      }
      delay(time3 - time2);
    }

    if (direc == 1) {
      serPump.write(550); //Anti clockwise maximum speed rotation (0 degrees)
      float total_time = 0;
      float delta = 0;
      float init_time = 0;
      while (total_time < pumping_time) {
        Device.updateSensors(BUBBLE, 1, B.Status());
        delta = 0;
        init_time = millis();
        while (B.Status() == 2) {
          Serial.println("Liquid detected");
          //Measure the time for whih the sensor detects liquid
          Device.updateSensors(BUBBLE, 1, B.Status());
          if (millis()-init_time >= pumping_time){
            break;
          }
        }
        delta = millis() - init_time;
        if(delta<10){
          delta=0;
        }
        total_time = total_time + delta;
        Serial.print("Total Time: ");
        Serial.println(total_time);
      }
      serPump.write(Stop);
    }


    /*if (direc == 1) {
      serPump.write(550); //Anti clockwise maximum speed rotation (0 degrees)
      while (B.Status() != 2) {
        // Pump while pipe gets filled with liquid
        // Poll the measurement from the sensor
        Device.updateSensors(BUBBLE, 1, B.Status());
        Serial.println("Pipe is empty");
      }
      int time1 = millis(); // time at which tube is filled with liquid
      Serial.println(time1);
      while (millis() - time1 < pumping_time){
        Serial.println("Pumping actual volume");
        // wait while it pumps the actual amount of liquid that we want
        if (B.Status() != 2) {
          // If there are any bubbles in the liquid take time measurement
          time2 = millis(); // Measurement of when bubble starts
          Serial.println("Bubble Detected");
          while (B.Status() != 2) {
            // Poll the measurement from the sensor
            Device.updateSensors(BUBBLE, 1, B.Status());
            Serial.println("While loop checking if bubble is gone");
          }
          time3 = millis(); // Measurement of when bubble finishes
        }
      }
      Serial.println("Extra time");
      delay(time3-time2); // Delay by the time spent in bubbles
      Serial.println("Extra time finished");
      serPump.write(Stop);
      }*/
      
  } //End if servo
}// End Function Pump_Bubble



// Stop pumping
void Pump::stop_pumping(void) {
  if (pump_type == 0) { // Servo
    serPump.write(Stop);
  }
  if (pump_type == 1) { // Stepper
    digitalWrite(Step, LOW);
  }
}// End function



// Set direction of pumping (no actual pumping); 1 = clockwise; 0 = anticlockwise
void Pump::set_dir(bool Direction) {
  dir = Direction;
}



// Get measurement for direction (0 for into reactor, 1 for reverse)
bool Pump::get_last_dir() {
  return Pump::dir;
}// End function



// Get measurement for volume pumped (in ml)
double Pump::get_last_vol() {
  return Pump::volume;
}// End function



// Get measurement for flowrate of SERVO (in ml per seconds)
double Pump::get_flow_rate() {
  return Pump::flowrate;
}// End function



// Set type of pump - SERVO = 0; STEPPER = 1
void Pump::set_pump_type(bool type_of_pump) {
  pump_type = type_of_pump;
}// End function



// Get pump type - SERVO = 0; STEPPER = 1
bool Pump::get_pump_type(void) {
  return Pump::pump_type;
}



// Set convertion ratio for servo pumps (for calibration)
void Pump::set_conv_ratio(double convertion) {
  if (pump_type == 0) {
    conv_ratio = convertion;
    //?????????????????????????????????????????????????????????????????????????????
    // Is it the constant 0.0052 in set_vol?
  }
}// End function



// Get convertion ratio (servo)
double Pump::get_conv_ratio(void) {
  if (pump_type == 0) {
    return conv_ratio;
  }
  else return 0;
}// End function



// Set the number of steps per ml in stepper pump (for calibration)
void Pump::set_steps_per_ml(double num_steps) {
  if (pump_type == 1) {
    steps_per_ml = num_steps;
  }
}// End function



// Get number of steps per ml (stepper)
double Pump::get_steps_per_nl(void) {
  if (pump_type == 0) {
    return steps_per_ml;
  }
  else return 0;
}// End function
