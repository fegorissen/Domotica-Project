#pragma once
#include "Device.h"

class Camera : public Device
{
public:
    Camera(std::string name);

    void toggle() override;
    std::string status() const override;

    void triggerMotion();

private:
    // vraag 5: useful and correct encapsulation
    // De encapsulatie is nuttig en correct omdat motionDetected_
    // private is: enkel bereikbaar via triggerMotion() en indirect
    // via status(). Van buitenaf kan niemand deze waarde rechtstreeks
    // fout instellen (bv. motion op true zetten terwijl de camera
    // uitstaat) -- de klasse zelf bewaakt wanneer en hoe deze waarde
    // verandert, wat de interne staat altijd consistent houdt.
    bool motionDetected_ = false;
};
