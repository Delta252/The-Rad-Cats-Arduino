List of commands:
[sID1000 rID PK1 V Sy] : Valve command,  Opens valve y, closes valves less than y, sets valves greater than y to middle position. ex. S2 = valve 2 opens, valve 1 closes, valve 3-5 middle.
[sID1000 rID PK1 U Sx] : Where x is a 5 long digit string consisting of only digits 0-2, sets valve position according to the digit in the string. ex. 01200 - valve 1 = open, valve 2 = closed, valve 3 = middle, valve 4 = open, valve 5 = open.
[sID1000 rID PK1 E Sx] : Servo command, rotates servo motor to x degrees (absolute, not relative). ex. S20 = 20 degrees rotation from 0.
[sID1000 rID PK1 P mx] : Peristaltic pump command, pumps x mls. ex. m2 pumps 2 mls.
[sID1000 rID PK1 Y Sx] : Syringe pump command, pumps x mls. ex. m2 pumps 2 mls.
[sID1000 rID PK2 M Sx Dy] : Mixer module command, x PWM, spins in y direction (1 = clockwise, 0 = anti-clockwise). ex. S80 D1 spins at 80 pwm clockwise.
[sID1000 rID PK1 I Sx] : Shutter command, Rotates shutter according to S parameter (x = 0: closed, x = 1: open, x = 2: middle). ex. S1 opens the shutter.
[sID1000 rID PK0 R] : Read command, reads sensors present on the module. Prints the following on the serial line: (sID rID1000 PKx SEN y Sz) where x is the packet size for a certain amount of sensors, y is the sensor type (T = Temperature, B = Bubble, S = LDS) and number, and z is value read from the sensor.