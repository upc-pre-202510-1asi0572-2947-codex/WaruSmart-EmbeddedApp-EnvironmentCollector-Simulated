#include "ModestIoT.h"
#include "DhtSensor.h"
#include "SoilMoistureSensor.h"
#include "IrrigationDevice.h"


DhtSensor dht(15);
SoilMoistureSensor soil(34);

IrrigationDevice device(dht, soil);

void setup() {
  device.setup();
}

void loop() {
  device.loop();
}
