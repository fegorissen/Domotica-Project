#include "Light.h"

namespace smarthome
{
    Light::Light(std::string name)
        : Device(name)
    {
    }

    // vraag 17 (Object Georiënteerde Project - Aanvullend): constructor forwarding
    Light::Light()
        : Light("Unnamed Light")
    {
    }

    void Light::toggle()
    {
        on_ = !on_;
    }

    // vraag 24 (Object Georiënteerde Project - Aanvullend): correct usage of inline function
    std::string Light::status() const
    {
        return onOffText(on_);
    }

    std::unique_ptr<Device> Light::clone() const
    {
        return std::make_unique<Light>(*this);
    }
}
