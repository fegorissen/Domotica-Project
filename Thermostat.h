#pragma once
#include "Device.h"

namespace smarthome
{
// vraag 3: useful and correct class
class Thermostat : public Device
{
public:
    // vraag 21 (Object Georiënteerde Project - Aanvullend): default values in function definition
    Thermostat(std::string name, double targetTemperature = 21.0);

    void toggle() override;
    std::string status() const override;
    std::unique_ptr<Device> clone() const override;

    // vraag 23 (Object Georiënteerde Project - Aanvullend): useful getters and setters for member variables
    double getTargetTemperature() const;
    void setTargetTemperature(double value);

private:
    double targetTemperature_;
};

// vraag 34 (Object Georiënteerde Project - Aanvullend): 2 useful
// (modern) call-by-references (1/2)
// 'thermostat' wordt als NIET-const referentie doorgegeven: deze
// functie wijzigt het originele object rechtstreeks (via
// setTargetTemperature), zonder pointer-syntax en zonder het
// object te moeten kopiëren of terug te geven.
void applyEnergySavingMode(Thermostat& thermostat, double degreesLower);
}
