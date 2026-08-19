#include "Thermostat.h"

// Let op: de default waarde (= 21.0) hoort enkel in de HEADER thuis,
// niet hier herhaald te worden -- dat zou een compile-fout geven.
Thermostat::Thermostat(std::string name, double targetTemperature)
    : Device(name), targetTemperature_(targetTemperature)
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

std::unique_ptr<Device> Thermostat::clone() const
{
    return std::make_unique<Thermostat>(*this);
}
