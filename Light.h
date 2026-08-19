#pragma once
#include "Device.h"

// vraag 6: useful and correct inheritance
// Light "is-a" Device: erft de volledige interface via public
// inheritance en voegt enkel zijn eigen data (brightness_) toe.
class Light : public Device
{
public:
    Light(std::string name);

    // vraag 12 (Object Georiënteerde Project - Aanvullend): at least 2 default constructors
    // vraag 17 (Object Georiënteerde Project - Aanvullend): constructor forwarding
    // Light() vraagt geen argumenten van de gebruiker, maar hergebruikt
    // de bestaande parameterized constructor via delegating
    // constructor-syntax i.p.v. logica te dupliceren.
    Light();

    // vraag 14 (Object Georiënteerde Project - Aanvullend): at least 2 copy constructors
    // Expliciet gedeclareerd (= default): Light heeft geen eigen
    // dynamisch geheugen, dus de door de compiler gegenereerde
    // memberwise-kopie is correct en voldoende. Wordt gebruikt door
    // clone() hieronder.
    Light(const Light&) = default;

    void toggle() override;
    std::string status() const override;

    // vraag 14 (Object Georiënteerde Project - Aanvullend): at least 2 copy constructors
    // clone() roept de copy constructor hierboven aan via make_unique.
    std::unique_ptr<Device> clone() const override;

private:
    bool brightness_ = 80;
};
