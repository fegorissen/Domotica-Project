#pragma once
#include "Device.h"

namespace smarthome
{
// vraag 6: useful and correct inheritance
// Light "is-a" Device: erft de volledige interface via public
// inheritance en voegt enkel zijn eigen data (brightness_) toe.
class Light : public Device
{
public:
    Light(std::string name);

    // vraag 12 (Object Georiënteerde Project - Aanvullend): at least 2 default constructors
    // vraag 17 (Object Georiënteerde Project - Aanvullend): constructor forwarding
    Light();

    // vraag 14 (Object Georiënteerde Project - Aanvullend): at least 2 copy constructors
    Light(const Light&) = default;

    void toggle() override;
    std::string status() const override;
    std::unique_ptr<Device> clone() const override;

    // vraag 23 (Object Georiënteerde Project - Aanvullend): useful getters and setters for member variables
    unsigned char getBrightness() const;
    void setBrightness(unsigned char value);

private:
    // vraag 28 (Object Georiënteerde Project - Aanvullend): 2 useful
    // unsigned chars or other better usage of memory efficient type
    // Helderheid gaat van 0 tot 100(%) -- een unsigned char (1
    // byte, bereik 0-255) is hiervoor ruim voldoende en veel
    // geheugenefficiënter dan bv. een int (4 bytes) voor een
    // waarde die toch nooit groter dan 100 wordt. Dit is het
    // TWEEDE voorbeeld naast Device::id_/nextId_.
    unsigned char brightness_ = 80;
};
}
