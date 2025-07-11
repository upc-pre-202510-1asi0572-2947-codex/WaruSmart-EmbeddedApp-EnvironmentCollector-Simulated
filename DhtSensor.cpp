#include "DhtSensor.h"

DhtSensor::DhtSensor(int pin) : pin(pin) {}

void DhtSensor::begin() {
    dht.setup(pin, DHTesp::DHT22);
}

void DhtSensor::update() {
    TempAndHumidity data = dht.getTempAndHumidity();
    temperature = data.temperature;
    humidity = data.humidity;
    valid = !(isnan(temperature) || isnan(humidity));
}
