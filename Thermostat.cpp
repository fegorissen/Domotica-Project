#include "Thermostat.h"

Thermostat::Thermostat(std::string name)
    : Device(name)
{
}

void Thermostat::toggle()
{
    on_ = !on_;
}

std::string Thermostat::status() const
{
    if (on_)
        return "verwarmt naar " + std::to_string(targetTemperature_) + " graden";
    else
        return "uit";
}
