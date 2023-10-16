# Class Overview
This class contains all of the functions needed to control the servo valves.


## Constructor
### Consutructor for Servo Valve
Takes 1 parameter: int pin_number in Arduino board 

Example: Valve myValve(2)



## Variables
int angleOpen: angle of servo when valve is open (state 0)

int angleClose: angle of servo when valve is closed (state 1)

int angleMid: angle of servo when valve is in middle position (state 2)

int pinSer: pin number of the servo

int a: variable that stores the sate of the valve (0 for open, 1 for closed, 2 for middle)



## Functions

### setUp(void)
Void function with no parameters. Should be called once in the setup function of main before the loop. 
The function attaches the pin and sends initial value. 

### set_pos(int pos)
Void function that sets the position of the valve to the state selected by the parameter pos. Pos can have 3 values: 0 (open), 1 (closed), 2 (middle). 
The function does not calibratet the position of the valve at each state. To do so, use the set_angle_lims function. 

### set_angle_lims(int angle0, int angle1)
Void function that updates the values of the anlges for opeing and closing the valves. angle0 calibrates angle in open position (state 0), and angle1 calibrates closed position (state 1). Middle position (state 2) is set to 90 by default. this cannot be calibrated with the funciton, but it can be calibrated by tuning variable angleMid. 

### get_pos_analog(void)
Int function that reads the angle of the servo.

### get_pos_digital(void)
Boold functions that returns the position of the servo (0 for closed and 1 for open).

### get_lim(bool pos)
Int function that returns the value of the angle of the servo at the indicated position (1 for open, 0 for closed).
