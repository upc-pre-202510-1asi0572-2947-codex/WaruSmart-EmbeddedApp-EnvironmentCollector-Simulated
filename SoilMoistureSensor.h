#ifndef SOIL_MOISTURE_SENSOR_H
#define SOIL_MOISTURE_SENSOR_H

#include <Arduino.h>

class SoilMoistureSensor {
public:
    SoilMoistureSensor(uint8_t analogPin, int minValue = 1680, int maxValue = 3620);

    void begin();
    void update();
    float getPercentage() const;

private:
    uint8_t pin;
    int minRaw;
    int maxRaw;
    float percentage;
};

#endif
