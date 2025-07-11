#include "SoilMoistureSensor.h"

/// @brief Constructor that sets pin and calibration range
SoilMoistureSensor::SoilMoistureSensor(uint8_t analogPin, int minValue, int maxValue)
    : pin(analogPin), minRaw(minValue), maxRaw(maxValue), percentage(0.0f) {}

/// @brief Configures the analog pin as input
void SoilMoistureSensor::begin() {
    pinMode(pin, INPUT);
}

/// @brief Reads analog value and calculates soil moisture percentage
void SoilMoistureSensor::update() {
    int raw = analogRead(pin);
    percentage = 100.0f * (maxRaw - raw) / (maxRaw - minRaw);
    percentage = constrain(percentage, 0.0f, 100.0f);
}

/// @brief Returns the last calculated moisture percentage
float SoilMoistureSensor::getPercentage() const {
    return percentage;
}
