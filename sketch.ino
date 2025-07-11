#include "ModestIoT.h"
#include "DhtSensor.h"
#include "SoilMoistureSensor.h"
#include "IrrigationDevice.h"

// Create sensor instances with their respective GPIO pins
DhtSensor dht(15);          // DHT22 connected to GPIO 15
SoilMoistureSensor soil(34); // Soil moisture sensor connected to GPIO 34

// Create the irrigation device with sensor references
IrrigationDevice device(dht, soil);

/// @brief Arduino setup function. Initializes sensors and network.
void setup() {
  device.setup();
}

/// @brief Arduino loop function. Reads sensors and sends data.
void loop() {
  device.loop();
}
