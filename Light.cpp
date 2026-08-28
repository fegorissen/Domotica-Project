#include "Light.h"
#include "MathUtils.h"

namespace smarthome
{
    Light::Light(std::string name)
        : Device(name)
    {
    }

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
        if (!on_)
        {
            return onOffText(on_);
        }
        return "aan (helderheid " + std::to_string(static_cast<int>(brightness_)) + "%)";
    }

    // vraag 36 (Object Georiënteerde Project - Aanvullend): useful container class
    std::string Light::getTypeName() const
    {
        return "Light";
    }

    std::unique_ptr<Device> Light::clone() const
    {
        return std::make_unique<Light>(*this);
    }

    unsigned char Light::getBrightness() const
    {
        return brightness_;
    }

    void Light::setBrightness(unsigned char value)
    {
        brightness_ = clamp<unsigned char>(value, 0, 100);
    }
}
