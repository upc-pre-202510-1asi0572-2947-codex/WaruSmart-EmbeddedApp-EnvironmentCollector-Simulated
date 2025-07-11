#ifndef RELAY_ACTUATOR_H
#define RELAY_ACTUATOR_H

#include "ModestIoT.h"

class RelayActuator : public Actuator {
public:
    RelayActuator(int pin);

    void begin();
    void activate(bool state) override;
    bool getState() const;

private:
    int pin;
    bool lastState = false;
};

#endif
