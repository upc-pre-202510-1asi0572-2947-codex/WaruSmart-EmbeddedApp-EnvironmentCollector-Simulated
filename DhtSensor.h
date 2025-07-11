#ifndef DHT_SENSOR_H
#define DHT_SENSOR_H

#include "DHTesp.h"

class DhtSensor {
public:
    DhtSensor(int pin);

    void begin();
    void update();

    float temperature = 0;
    float humidity = 0;
    bool valid = false;

private:
    int pin;
    DHTesp dht;
};

#endif
