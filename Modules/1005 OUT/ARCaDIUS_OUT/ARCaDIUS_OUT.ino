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
int Num_of_Syringes = 0;
int ResetPin = 3;
bool isSetUp = false;

ASerial Device(DeviceDesc, Device_ID, Sender_ID, Num_of_Pumps, Num_of_Valves, Num_of_Shutter, Num_of_Temp, Num_of_Bubble, Num_of_Liquid, Num_of_Mixer, Num_of_Syringes, ResetPin);
Valve Valve1(3, 65, 127);
Valve Valve2(5, 65, 127);
Valve Valve3(6, 65, 128);
Valve Valve4(9, 65, 127);
Valve Valve5(10, 66, 130);
ValveHandler valveController(Valve1, Valve2, Valve3, Valve4, Valve5);
Pump P1(11);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Device.Start();
  Serial.println(Device.GetDeviceConnectedStatus());
}

void loop() {
  //Checks if CONF command has been returned, then sets up
  if(Device.GetDeviceConnectedStatus() && !isSetUp)
  {
    Valve1.setUp();
    Valve2.setUp();
    Valve3.setUp();
    Valve4.setUp();
    Valve5.setUp();
    P1.setUp();
    sensors.begin();
    isSetUp = true;
  }
  if (Device.GotCommand()) {
    sensors.requestTemperatures();
    Serial.println(sensors.getTempCByIndex(0));
    Device.updateSensors(TEMP, 1, sensors.getTempCByIndex(0));
    switch (Device.GetCommand()) {
      case PUMP: 
        P1.set_vol(Device.getPumpMls(),Device.getPumpDir());
        break;
      case MIXER: // Enter code for mixer here
        break;
      case VALVE:
        valveController.setPositionOfValves(Device.getValve());
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
