#pragma once
#include "Device.h"

class Thermostat : public Device
{
public:
    Thermostat(std::string name);

    void toggle() override;
    std::string status() const override;

private:
    double targetTemperature_ = 21.0;
};
