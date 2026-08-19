#include "Thermostat.h"
#include "MathUtils.h"

namespace
{
constexpr double MIN_TEMP = 10.0;
constexpr double MAX_TEMP = 30.0;
}

// vraag 25 (Object Georiënteerde Project - Aanvullend): useful template function or class
// clamp<double> wordt hier automatisch gegenereerd door de compiler
// om de starttemperatuur meteen binnen een geldig bereik te houden.
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

std::unique_ptr<Device> Thermostat::clone() const
{
    return std::make_unique<Thermostat>(*this);
}

double Thermostat::getTargetTemperature() const
{
    return targetTemperature_;
}

// vraag 25 (Object Georiënteerde Project - Aanvullend): useful template function or class
// Zelfde clamp<double> hier hergebruikt -- dit is precies waarom een
// template nuttig is: geen gedupliceerde begrenzingslogica tussen de
// constructor en deze setter.
void Thermostat::setTargetTemperature(double value)
{
    targetTemperature_ = clamp(value, MIN_TEMP, MAX_TEMP);
}
