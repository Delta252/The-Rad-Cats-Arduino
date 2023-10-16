#include "ARCaDIUS_Serial.h"
#include "Valve.h"
#include "Pump.h"
#include "Shutter.h"
#include "LDSensor.h"
#include "BubbleSensor.h"
#include "MixerMotor.h"


String DeviceDesc = "This is an example string";
int Device_ID = 1001;
int Sender_ID = 1000;
int Num_of_Pumps = 2;
int Num_of_Valves = 0;
int Num_of_Shutter = 1;
int Num_of_Mixer = 1;
int Num_of_Temp = 0;
int Num_of_Bubble = 1;
int Num_of_LDS = 1;
int ResetPin = 3;

ASerial Device(DeviceDesc, Device_ID, Sender_ID, Num_of_Pumps, Num_of_Valves, Num_of_Shutter, Num_of_Temp, Num_of_Bubble, Num_of_LDS, Num_of_Mixer, ResetPin);
Pump P1(9);
Valve myvalve(5, 65, 120);
Shutter shutter(54, 7);
LDSensor liquid(3);
BubbleSensor bubble(A0, 6);
MixerMotor MagMix(10,4,11);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.setTimeout(1000);
  Serial.println("start");
  Device.Start();
  myvalve.setUp();
  P1.setUp();
  shutter.Initialise();
  bubble.setupBS();
  liquid.SetUpLDS();
  MagMix.SetUpMotor();
}



void loop() {
  // Enter the subsystem code in the switch statement, delete all the serial prints.
  if (Device.GotCommand()) {
    //[sID1000 rID1001 PK1 R]
    Device.updateSensors(BUBBLE, 1, bubble.Status());
    Device.updateSensors(LDS, 1, liquid.StatusLDS());
    switch (Device.GetCommand()) {
      case PUMP: // Enter code for pumping here
        Serial.println("The pump number is: " + (String)Device.getPump());
        Serial.println("The pump volume in mls is: " + (String)Device.getPumpMls());
        Serial.println("The pump direction is: " + (String)Device.getPumpDir());
        switch (Device.getPump()) {
          case 1:
            //P1.set_vol(Device.getPumpMls(),Device.getPumpDir());
            break;
          default:
            break;
        }
        break;
      case MIXER: //[sID1000 rID1001 PK3 M1 S1 D1]
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
        switch (Device.getValve()) {
          // [sID1000 rID1001 PK2 V1 S0]
          case 1:
            myvalve.set_pos(Device.getValveState());
            Serial.println("1The valve state  is: " + (String)Device.getValveState());
            Serial.println("2The valve state  is: " + (String)myvalve.get_pos_digital());
            Serial.println("3The valve angle  is: " + (String)myvalve.get_pos_analog());
            
            break;
          default:
            break;
        }
        break;

      case SHUTTER:  
        Serial.println("The shutter number is: " + (String)Device.getShutter());
        switch (Device.getShutterPos()) {
          case 0:
            //Serial.println("The shutter position  is: " + (String)Device.getShutterPos());
            shutter.moveto(0, 0); //change 0 to 1 for control
            break;
          case 1:
            //Serial.println("The shutter position  is: " + (String)Device.getShutterPos());
            shutter.moveto(120, 0); //change 0 to 1 for control
            break;
          case 2:
            //Serial.println("The shutter position  is: " + (String)Device.getShutterPos());
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
