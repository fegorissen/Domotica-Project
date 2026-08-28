#include "Light.h"
#include "MathUtils.h"

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
        if (!on_)
        {
            return onOffText(on_);
        }
        return "aan (helderheid " + std::to_string(static_cast<int>(brightness_)) + "%)";
    }

    std::unique_ptr<Device> Light::clone() const
    {
        return std::make_unique<Light>(*this);
    }

    unsigned char Light::getBrightness() const
    {
        return brightness_;
    }

    // vraag 25 (Object Georiënteerde Project - Aanvullend): useful template function or class
    // Hergebruikt dezelfde clamp<T>()-template als Thermostat, nu voor
    // het type unsigned char in plaats van double -- exact waarom een
    // template nuttig is: één functie, meerdere types.
    void Light::setBrightness(unsigned char value)
    {
        brightness_ = clamp<unsigned char>(value, 0, 100);
    }
}
