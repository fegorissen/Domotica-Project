#pragma once
#include "Device.h"

// vraag 3: useful and correct class
// Thermostat is een nuttige en correcte klasse omdat het één duidelijke,
// afgebakende verantwoordelijkheid heeft: één verwarmingstoestel
// voorstellen. Het hergebruikt alles wat gemeenschappelijk is via
// Device (naam, aan/uit), en voegt enkel zijn eigen, specifieke data
// (targetTemperature_) en gedrag toe. Net als Light, DoorLock en
// Camera doet het precies één ding, wat de code overzichtelijk en
// makkelijk uitbreidbaar maakt.
class Thermostat : public Device
{
public:
    Thermostat(std::string name);

    void toggle() override;
    std::string status() const override;

private:
    double targetTemperature_ = 21.0;
};
