#include "DhtSensor.h"

/// @brief Constructor that stores the GPIO pin
DhtSensor::DhtSensor(int pin) : pin(pin) {}

/// @brief Initializes the DHT sensor using the specified pin
void DhtSensor::begin() {
    dht.setup(pin, DHTesp::DHT22);
}

/// @brief Reads temperature and humidity, updates internal values and validity flag
void DhtSensor::update() {
    TempAndHumidity data = dht.getTempAndHumidity();
    temperature = data.temperature;
    humidity = data.humidity;
    valid = !(isnan(temperature) || isnan(humidity));
}
