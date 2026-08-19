#pragma once
#include "Device.h"

// vraag 3: useful and correct class
// Thermostat is een nuttige en correcte klasse omdat het één duidelijke,
// afgebakende verantwoordelijkheid heeft: één verwarmingstoestel
// voorstellen. Het hergebruikt alles wat gemeenschappelijk is via
// Device (naam, aan/uit), en voegt enkel zijn eigen, specifieke data
// (targetTemperature_) en gedrag toe.
class Thermostat : public Device
{
public:
    // vraag 21 (Object Georiënteerde Project - Aanvullend): default values in function definition
    // targetTemperature heeft een default waarde (21.0): de aanroeper
    // kan Thermostat("Verwarming") schrijven (gebruikt dan 21 graden),
    // of expliciet Thermostat("Verwarming", 18.5) om een andere
    // starttemperatuur op te geven -- zonder dat er twee aparte
    // constructors nodig zijn.
    Thermostat(std::string name, double targetTemperature = 21.0);

    void toggle() override;
    std::string status() const override;
    std::unique_ptr<Device> clone() const override;

private:
    double targetTemperature_;
};
