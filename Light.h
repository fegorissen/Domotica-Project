#pragma once
#include "Device.h"

// vraag 6: useful and correct inheritance
// De overerving is nuttig en correct omdat Light via "public Device"
// een correcte "is-a"-relatie aangaat: elke Light ís ook een Device,
// en kan overal gebruikt worden waar een Device verwacht wordt (bv.
// in Room's vector<unique_ptr<Device>>). Light hoeft de gemeenschap-
// pelijke code (naam bijhouden, aan/uit-status) niet te herhalen --
// dat regelt Device al -- en voegt enkel zijn eigen, specifieke data
// (brightness_) toe.
class Light : public Device
{
public:
    Light(std::string name);

    void toggle() override;
    std::string status() const override;

private:
    bool brightness_ = 80;
};
