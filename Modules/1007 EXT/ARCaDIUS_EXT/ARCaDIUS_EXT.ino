#include "ARCaDIUS_Serial.h"
#include "Extract.h"
#include "Pump.h"
#include "Valve.h"

String DeviceDesc = "Module = Extract";
int Device_ID = 1007;
int Sender_ID = 1000;
int Num_of_Pumps = 1;
int Num_of_Valves = 5;
int Num_of_Shutter = 0;
int Num_of_Mixer = 0;
int Num_of_Temp = 0;
int Num_of_Bubble = 0;
int Num_of_LDS = 1;
int ResetPin = 3;
bool isSetUp = false;

ASerial Device(DeviceDesc, Device_ID, Sender_ID, Num_of_Pumps, Num_of_Valves, Num_of_Shutter, Num_of_Temp, Num_of_Bubble, Num_of_LDS, Num_of_Mixer, ResetPin);

Pump P5(5);
Extract E1(6);

void setup() {
  Serial.begin(115200);
  Device.Start();
}

void loop() {
  if(Device.GetDeviceConnectedStatus() && !isSetUp)
  {
    isSetUp = true;
  }
  if(Device.GetDeviceConnectedStatus() && !isSetUp)
  {
    Serial.println("hi");
    P5.setUp();
    E1.setUp();
    isSetUp = true;
  }
  if (Device.GotCommand()) {
    switch (Device.GetCommand()) {
      case PUMP:
        Serial.println("pump number: " + (String)Device.getPump());
        Serial.println("pump volume: " + (String)Device.getPumpMls());
        P5.set_vol(Device.getPumpMls(),Device.getPumpDir());
        break;
      case MIXER: // Enter code for mixer here
        Serial.println("The mixer number is: " + (String)Device.getMixer());
        Serial.println("The mixer speed is: " + (String)Device.getMixerSpeed());
        Serial.println("The mixer direction is: " + (String)Device.getMixerDir());
        break;
      case VALVE:
        break;
      case SHUTTER: // Enter code for shutter here
        Serial.println("The shutter number is: " + (String)Device.getShutter());
        Serial.println("The shutter position  is: " + (String)Device.getShutterPos());
        break;
      default: // Leav  t
        break;
      case EXTRACT: //[sID1000 rID1006 PK2 E1 S0]
        E1.set_pos(Device.getExtractPos());
        break;
    }
    delay(100);
    Device.FinishedCommand();
  }
}
