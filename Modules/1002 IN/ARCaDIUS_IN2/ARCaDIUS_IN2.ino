#include "ARCaDIUS_Serial.h"
#include "Pump.h"

String DeviceDesc = "Module = Input 2";
int Device_ID = 1002;
int Sender_ID = 1000;
int Num_of_Pumps = 1;
int Num_of_Valves = 0;
int Num_of_Shutter = 0;
int Num_of_Mixer = 0;
int Num_of_Temp = 0;
int Num_of_Bubble = 0;
int Num_of_LDS = 1;
int ResetPin = 3;

ASerial Device(DeviceDesc, Device_ID, Sender_ID, Num_of_Pumps, Num_of_Valves, Num_of_Shutter, Num_of_Temp, Num_of_Bubble, Num_of_LDS, Num_of_Mixer, ResetPin);
Pump P1(7,8,4);

int Liquid = 3;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Device.Start();
  P1.setUp();
  pinMode(Liquid, INPUT);
}


void loop() {
  Device.updateSensors(LDS, 1, digitalRead(Liquid)); 
  if (Device.GotCommand()) {
    //[sID1000 rID1001 PK1 R]   
    switch (Device.GetCommand()) {      
      case PUMP: //[sID1000 rID1001 PK2 P1 m3.0]
        /*
        Serial.println("The pump number is: " + (String)Device.getPump());
        Serial.println("The pump volume in mls is: " + (String)Device.getPumpMls());
        Serial.println("The pump direction is: " + (String)Device.getPumpDir());*/
        switch (Device.getPump()) {
          case 1:
            P1.set_vol(Device.getPumpMls(),Device.getPumpDir());
            break;
          default:
            break;
        }
        break;
      case MIXER: //[sID1000 rID1001 PK3 M1 S1 D1]
        Serial.println("The mixer number is: " + (String)Device.getMixer());
        Serial.println("The mixer speed is: " + (String)Device.getMixerSpeed());
        Serial.println("The mixer direction is: " + (String)Device.getMixerDir());
        break;

      case VALVE: // Enter code for Valve here
        Serial.println("The valve number is: " + (String)Device.getValve());
        break;

      case SHUTTER:  
        Serial.println("The shutter number is: " + (String)Device.getShutter());

      default: // Leave this, its just the default
        break;
    }
    delay(100);
    Device.FinishedCommand();

  }
}
