#include "ARCaDIUS_Serial.h"
#include "Syringe_Motor.h"

String DeviceDesc = "Module = SyringePump";
int Device_ID = 1009;
int Sender_ID = 1000;
int Num_of_Pumps = 0;
int Num_of_Valves = 0;
int Num_of_Shutter = 0;
int Num_of_Mixer = 0;
int Num_of_LDS = 0;
int Num_of_Temp = 0;
int Num_of_Bubble = 0;
int Num_of_Syringe = 1;
int ResetPin = 3;

bool isSetUp = false;

ASerial Device(DeviceDesc, Device_ID, Sender_ID, Num_of_Pumps, Num_of_Valves, Num_of_Shutter, Num_of_Temp, Num_of_Bubble, Num_of_LDS, Num_of_Mixer, Num_of_Syringe, ResetPin);
StepperMotor myMotor(12);

void setup() {
  Serial.begin(115200);
  Device.Start();
}

void loop() {
  if(Device.GetDeviceConnectedStatus() && !isSetUp)
  {
    myMotor.setUp();
    isSetUp = true;
  }
  if (Device.GotCommand()) {
    switch (Device.GetCommand()) {
      case PUMP: 
        Serial.println("pump number: " + (String)Device.getPump());
        Serial.println("pump volume: " + (String)Device.getPumpMls());
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
      case SYRINGE:
        Serial.println("The Syringe volume is: " + (String)Device.getSyringeVolume());
        Serial.println("The Syringe Type is: " + (String)Device.getSyringeType());
        myMotor.pumpVolume(Device.getSyringeVolume(), Device.getSyringeType());
        break;
      default: // Leave this, its just the default //[sID1000 rID1006 PK2 E1 S0]
        break;
    }
    delay(100);
    Device.FinishedCommand();
  }
}
