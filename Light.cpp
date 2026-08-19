#include "Light.h"

Light::Light(std::string name)
    : Device(name)
{
}

// vraag 17 (Object Georiënteerde Project - Aanvullend): constructor forwarding
// Roept de bestaande parameterized constructor aan met een standaard-
// naam, i.p.v. de logica van Device(name) hier te herhalen.
Light::Light()
    : Light("Unnamed Light")
{
}

void Light::toggle()
{
    on_ = !on_;
}

// vraag 24 (Object Georiënteerde Project - Aanvullend): correct usage of inline function
// Gebruikt de inline functie onOffText() uit Device.h i.p.v. hier
// opnieuw een if/else te schrijven.
std::string Light::status() const
{
    return onOffText(on_);
}

std::unique_ptr<Device> Light::clone() const
{
    return std::make_unique<Light>(*this);
}
