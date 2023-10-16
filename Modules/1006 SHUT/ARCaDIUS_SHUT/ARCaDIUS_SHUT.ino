#include "ARCaDIUS_Serial.h"
#include "Shutter.h"
#include "MixerMotor.h"

String DeviceDesc = "Module = shutter";
int Device_ID = 1005;
int Sender_ID = 1000;
int Num_of_Pumps = 0;
int Num_of_Valves = 0;
int Num_of_Shutter = 1;
int Num_of_Mixer = 0;
int Num_of_Temp = 1;
int Num_of_Bubble = 0;
int Num_of_LDS = 0;
int ResetPin = 3;

ASerial Device(DeviceDesc, Device_ID, Sender_ID, Num_of_Pumps, Num_of_Valves, Num_of_Shutter, Num_of_Temp, Num_of_Bubble, Num_of_LDS, Num_of_Mixer, ResetPin);

Shutter shutter(54, 3);
MixerMotor MagMix(10,11,9);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Device.Start();
  shutter.Initialise();
  MagMix.SetUpMotor();
}

void loop() {
  // Enter the subsystem code in the switch statement, delete all the serial prints.
  if (Device.GotCommand()) {
    //[sID1000 rID1005 PK1 R]
    switch (Device.GetCommand()) {
      case PUMP: // Enter code for pumping here
        break;
      case MIXER: //[sID1000 rID1005 PK3 M1 S1 D1] at 80 pwm=> max time = 4:41 before stalling
        Serial.println("The mixer number is: " + (String)Device.getMixer());
        Serial.println("The mixer speed is: " + (String)Device.getMixerSpeed());
        Serial.println("The mixer direction is: " + (String)Device.getMixerDir());
        if (Device.getMixerSpeed() == 0) {
          MagMix.StopMotor();
        }
        else {
          MagMix.SetSpeed(Device.getMixerSpeed());
        }
        break;

      case VALVE: // Enter code for Valve here
        Serial.println("The valve number is: " + (String)Device.getValve());
        break;

      case SHUTTER:  
        Serial.println("The shutter number is: " + (String)Device.getShutter());
        Serial.println("Shutter position: " + (String)Device.getShutterPos());
        //[sID1000 rID1005 PK3 I1 S1]
        switch (Device.getShutterPos()) {
          case 0:
            shutter.moveto(0, 0); //change 0 to 1 for control
            break;
          case 1:
            shutter.moveto(120, 0); //change 0 to 1 for control
            break;
          case 2:
            shutter.moveto(240, 0); //change 0 to 1 for control
            break;
          default:
            break;
        }

      default: // Leave this, its just the default
        break;
    }
    delay(100);
    Device.FinishedCommand();
  }
}
