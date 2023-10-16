#ifndef Pump_H
#define Pump_H

#include <Arduino.h>
#include "Servo.h"
#include "BubbleSensor.h"
#include "ARCaDIUS_Serial.h"

class Pump {
  private:
    Servo serPump;
    int pinNum;     // pin number (should be 2 for the servo)
    //enum pump_type {servo=0, stepper=1};
    bool pump_type; // 0 = servo; 1 = stepper
    float flowrate = 0;
    float volume = 0;
    bool dir = 0;
    int Stop = 1500; // Stopping value for servo pump
    double conv_ratio = 0.0052;   // conversions of servo (?) to ml
    double steps_per_ml = 9293.4; // Number of steps per ml

    int StepsPerRev = 3200;
    int dirStep = 5;            // Pin number for direction - SET TO 5
    int Step = 2;              // Pin number with actual signal - SET TO 2
    int EN = 8;                // Pin number to activate/deactivate - SET TO 8
    float step2ml = 1648.8;

  public:
    // Constructor and initial settings - variable type_of_pump: 0 = servo, 1 = stepper
    Pump(int pinPump): pinNum(pinPump), pump_type(0) {}
    // Constructor for servo pump
    // Takes pin number on arduino as parameter
  
    Pump(int d, int s, int e): dirStep(d), Step(s), EN(e), pump_type(1) {}
    // Constructor of stepper pump
    // Takes number for direction pin, step (signal) pin, and enable pin in the arduino

    // Pump liquid with feedback from the bubble sensor
    void pump_bubble(float vol, bool direc, BubbleSensor B, ASerial Device);

    void setUp(void);
    // To be used in void setup()

    void set_vol(float vol, bool direc);
    // Set direction (binary) and volume (in ml) to be pumped
    // Works for both servo and stepper pumps

    void stop_pumping(void);
    // Stop pumping immediately

    void set_dir(bool Direction);
    // Set direction of pumping (no actual pumping); 1 = clockwise; 0 = anticlockwise

    bool get_last_dir();
    // Get measurement for direction (0 for into reactor, 1 for reverse)

    double get_last_vol();
    // Get measurement for last volume pumped (in ml)

    double get_flow_rate();
    // Get measurement for flowrate of SERVO (in ml per seconds)

    void set_pump_type(bool type_of_pump);
    // Set type of pump - SERVO = 0; STEPPER = 1

    bool get_pump_type(void);
    // Get pump type - SERVO = 0; STEPPER = 1
  
    void set_conv_ratio(double convertion);
    // Set convertion ratio for servo pumps (for calibration)

    double get_conv_ratio(void);
    // Get convertion ratio (servo)

    void set_steps_per_ml(double num_steps);
    // Set the number of steps per ml in stepper pump (for calibration)

    double get_steps_per_nl(void);
    // Get number of steps per ml (stepper)

}; // End Class Pump

#endif
