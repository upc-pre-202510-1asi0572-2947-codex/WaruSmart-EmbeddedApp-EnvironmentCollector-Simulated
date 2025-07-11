#include "SoilMoistureSensor.h"

SoilMoistureSensor::SoilMoistureSensor(uint8_t analogPin, int minValue, int maxValue)
    : pin(analogPin), minRaw(minValue), maxRaw(maxValue), percentage(0.0f) {}

void SoilMoistureSensor::begin() {
    pinMode(pin, INPUT);
}

void SoilMoistureSensor::update() {
    int raw = analogRead(pin);
    percentage = 100.0f * (maxRaw - raw) / (maxRaw - minRaw);
    percentage = constrain(percentage, 0.0f, 100.0f);
}

float SoilMoistureSensor::getPercentage() const {
    return percentage;
}
