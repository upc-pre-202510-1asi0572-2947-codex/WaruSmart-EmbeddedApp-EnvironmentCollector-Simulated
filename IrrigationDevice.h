#ifndef IRRIGATION_DEVICE_H
#define IRRIGATION_DEVICE_H

#include "ModestIoT.h"
#include "DhtSensor.h"
#include "SoilMoistureSensor.h"

class IrrigationDevice : public Device {
public:
    IrrigationDevice(DhtSensor& dhtSensor, SoilMoistureSensor& soil);

    void setup() override;
    void loop() override;

private:
    DhtSensor& dht;
    SoilMoistureSensor& soil;

    void connectWiFi();
    void sendData(const String& jsonPayload);
};

#endif
