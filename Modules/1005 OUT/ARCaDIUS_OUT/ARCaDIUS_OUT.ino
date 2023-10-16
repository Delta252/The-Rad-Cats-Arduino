#include "ARCaDIUS_Serial.h"
#include "OneWire.h"
#include "DallasTemperature.h"
#include "Valve.h"
#include "Pump.h"

#define ONE_WIRE_BUS 12
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);
String DeviceDesc = "Module = Output";
int Device_ID = 1005;
int Sender_ID = 1000;
int Num_of_Pumps = 1;
int Num_of_Valves = 5;
int Num_of_Shutter = 0;
int Num_of_Mixer = 0;
int Num_of_Temp = 1;
int Num_of_Liquid = 0;
int Num_of_Bubble = 0;
int ResetPin = 3;

ASerial Device(DeviceDesc, Device_ID, Sender_ID, Num_of_Pumps, Num_of_Valves, Num_of_Shutter, Num_of_Temp, Num_of_Bubble, Num_of_Liquid, Num_of_Mixer, ResetPin);
Valve Valve1(3, 65, 127);
Valve Valve2(5, 65, 127);
Valve Valve3(6, 65, 128);
Valve Valve4(9, 65, 127);
Valve Valve5(10, 66, 130);
Pump P1(11);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Device.Start();
  
  Valve1.setUp();
  Valve2.setUp();
  Valve3.setUp();
  Valve4.setUp();
  Valve5.setUp();
  P1.setUp();
  sensors.begin();
  
}

void loop() {
  
  if (Device.GotCommand()) {
    sensors.requestTemperatures();
    Device.updateSensors(TEMP, 1, sensors.getTempCByIndex(0));
    switch (Device.GetCommand()) {
      case PUMP: 
        switch (Device.getPump()) {//[sID1000 rID1004 PK3 P1 m5.00]
          case 1:
            P1.set_vol(Device.getPumpMls(),Device.getPumpDir());
            break;
          default:
            break;
        }
        break;
      case MIXER: // Enter code for mixer here
        break;
      case VALVE:
        switch (Device.getValve()) {//test [sID1000 rID1004 PK2 V1 S0]
          case 1:
            Valve1.set_pos(Device.getValveState());
            Serial.println("valve number: " + (String)Device.getValve());
            Serial.println("valve state:  " + (String)Valve1.get_pos_digital());
            Serial.println("valve angle:  " + (String)Valve1.get_pos_analog());
            break;
          case 2:
            Valve2.set_pos(Device.getValveState());
            Serial.println("valve number: " + (String)Device.getValve());
            Serial.println("valve state:  " + (String)Valve2.get_pos_digital());
            Serial.println("valve angle:  " + (String)Valve2.get_pos_analog());
            break;
          case 3:
            Valve3.set_pos(Device.getValveState());
            Serial.println("valve number: " + (String)Device.getValve());
            Serial.println("valve state:  " + (String)Valve3.get_pos_digital());
            Serial.println("valve angle:  " + (String)Valve3.get_pos_analog());
            break;
          case 4:
            Valve4.set_pos(Device.getValveState());
            Serial.println("valve number: " + (String)Device.getValve());
            Serial.println("valve state:  " + (String)Valve4.get_pos_digital());
            Serial.println("valve angle:  " + (String)Valve4.get_pos_analog());
            break;
          case 5:
            Valve5.set_pos(Device.getValveState());
            Serial.println("valve number: " + (String)Device.getValve());
            Serial.println("valve state:  " + (String)Valve5.get_pos_digital());
            Serial.println("valve angle:  " + (String)Valve5.get_pos_analog());
            break;
          default:
            break;
        }
        
        break;
      case SHUTTER: // Enter code for shutter here
        Serial.println("The shutter number is: " + (String)Device.getShutter());
        Serial.println("The shutter position  is: " + (String)Device.getShutterPos());
        break;
      default: // Leave this, its just the default
        break;
    }
    delay(100);
    Device.FinishedCommand();
  }
}
