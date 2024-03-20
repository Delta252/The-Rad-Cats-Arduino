#include "OneWire.h"
#include "DallasTemperature.h"

// Data wire is plugged into port 3 on the Arduino
#define ONE_WIRE_BUS 12

// Setup a oneWire instance to communicate with any OneWire devices (not just Maxim/Dallas temperature ICs)
OneWire oneWire(ONE_WIRE_BUS);

// Pass our oneWire reference to Dallas Temperature.
DallasTemperature sensors(&oneWire);

void setup(void) {
    Serial.begin(115200);
    sensors.begin();
    Serial.print(sensors.getDeviceCount(), DEC);
}

void loop(void) {
    // request to all devices on the bus
    sensors.requestTemperatures(); // Send the command to get temperatures
    Serial.println(sensors.getTempCByIndex(0));
}
