#ifndef SOIL_MOISTURE_SENSOR_H
#define SOIL_MOISTURE_SENSOR_H

#include <Arduino.h>

/// @brief Handles analog readings and moisture percentage calculation from a soil moisture sensor
class SoilMoistureSensor {
public:
    /// @brief Constructor
    /// @param analogPin Analog input pin connected to the sensor
    /// @param minValue Raw analog value for 100% moisture (wet soil)
    /// @param maxValue Raw analog value for 0% moisture (dry soil)
    SoilMoistureSensor(uint8_t analogPin, int minValue = 1680, int maxValue = 3620);

    /// @brief Initializes the sensor (if needed)
    void begin();

    /// @brief Reads the analog value and updates the percentage
    void update();

    /// @brief Returns the latest soil moisture percentage (0–100%)
    float getPercentage() const;

private:
    uint8_t pin;       // Analog input pin
    int minRaw;        // Minimum expected raw value (wet soil)
    int maxRaw;        // Maximum expected raw value (dry soil)
    float percentage;  // Calculated soil moisture percentage
};

#endif
