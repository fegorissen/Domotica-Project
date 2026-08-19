#include "Light.h"

Light::Light(std::string name)
    : Device(name)
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
