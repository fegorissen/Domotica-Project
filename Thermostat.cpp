#include "Thermostat.h"
#include "MathUtils.h"

namespace smarthome
{
namespace
{
constexpr double MIN_TEMP = 10.0;
constexpr double MAX_TEMP = 30.0;
}

// vraag 25 (Object Georiënteerde Project - Aanvullend): useful template function or class
Thermostat::Thermostat(std::string name, double targetTemperature)
    : Device(name), targetTemperature_(clamp(targetTemperature, MIN_TEMP, MAX_TEMP))
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

// vraag 36 (Object Georiënteerde Project - Aanvullend): useful container class
std::string Thermostat::getTypeName() const
{
    return "Thermostat";
}

std::unique_ptr<Device> Thermostat::clone() const
{
    return std::make_unique<Thermostat>(*this);
}

double Thermostat::getTargetTemperature() const
{
    return targetTemperature_;
}

void Thermostat::setTargetTemperature(double value)
{
    targetTemperature_ = clamp(value, MIN_TEMP, MAX_TEMP);
}

// vraag 34 (Object Georiënteerde Project - Aanvullend): 2 useful (modern) call-by-references (1/2)
void applyEnergySavingMode(Thermostat& thermostat, double degreesLower)
{
    thermostat.setTargetTemperature(thermostat.getTargetTemperature() - degreesLower);
}
}
