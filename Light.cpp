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

std::string Light::status() const
{
    if (on_)
        return "aan";
    else
        return "uit";
}

std::unique_ptr<Device> Light::clone() const
{
    return std::make_unique<Light>(*this);
}
