# Class Overview
This class contains all of the functions needed to control both servo and stepper pumps. The class has two constructors, one for stepper and one for servo motors. 


## Constructors
### Consutructor for Servo Pump
Takes 2 parameters in order: int pin_number in Arduino board and bool type_of_pump (0 for servo). 
Example: Pump servoPump(2,0)
### Constructor for Stepper Pump
Takes 4 parameters in order: int direction_pin (initialised to 5), int step_pin (initialised to 2), int enable_pin (initialised to 8), bool type_of_pump (1 for stepper)
Example: Pump stepperPump(5,2,8,1)


## Variables
int pinNum: pin number in arduino (for servo only)

bool pump_type: boolean variable to indicate the type of pump - servo = 0; stepper = 1

float flowrate: variable to get a measurement of the flowrate (use get_flow_rate function)

float volume: variable to indicate the amount of volume being pumped 

bool dir: indicates the direction of the liquid (servo)

int Stop: stopping angle for servo pump

double conv_ratio: conversion ratio for servo pump

double steps_per_ml: number of steps required to pump 1 ml (stepper)

int StepsPerRev: number of steps in a revolution (stepper)

int dirStep: pin number for direction of the pump (stepper)

int Step: pin number with actual PWM signal (stepper)

int EN: pin number to activate/deactivate stepper 


## Functions

### setUp(void)
Void function with no parameters. Should be called once in the setup function of main before the loop. 
The function attaches all pins and sends initial values. 

### set_vol(float vol, bool direc)
Void function that takes 2 parameters in order: volume that needs to be pumped (float), and direction of the pumping (boolean).
The pumps will stop after desire volume has been reached.
The function is not used to calibrate the pumps, only pumping the volume selected.

### stop_pumping(void)
Void function that makes the pumps stop pumping. 
The function does not need to be called after set_vol, it should be used in interrupts.

### set_dir(bool Direction)
Void function that sets the direction of the pumping.

### get_last_dir()
Bool function that reads the direction of the pump.

### get_last_vol)()
double function that reads the last volume pumped.

### get_flow_rate()
double function that reads the last flowrate.

### set_pump_type(bool type_of_pump)
Void function that sets the type of the pump. 
Servo = 0; Stepper = 1

### get_pump_type(bool type_of_pump)
Bool function that reads the type of the pump. 
Servo = 0; Stepper = 1

### set_conv_ratio(double convertion)
Void function that sets the convertion ratio of servo pumps.
Used for calibration.

### get_conv_ratio(void)
Double function that reads the conversion ratio of the servo pump.

### set_steps_per_ml(double num_steps)
Void function that sets the number of steps per ml  of stepper pumps.
Used for calibration.

### get_steps_per_ml(void)
Double function that reads the number of steps per ml in stepper motor.
