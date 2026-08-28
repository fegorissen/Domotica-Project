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

private:
    bool brightness_ = 80;
};
}
