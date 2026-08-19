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
    // starttemperatuur op te geven.
    Thermostat(std::string name, double targetTemperature = 21.0);

    void toggle() override;
    std::string status() const override;
    std::unique_ptr<Device> clone() const override;

    // vraag 23 (Object Georiënteerde Project - Aanvullend): useful getters and setters for member variables
    // Getter: geeft de huidige doeltemperatuur terug.
    double getTargetTemperature() const;

    // vraag 23 (Object Georiënteerde Project - Aanvullend): useful getters and setters for member variables
    // Setter met validatie: begrenst de temperatuur tussen 10 en 30
    // graden (een realistisch bereik voor een thermostaat), i.p.v.
    // elke willekeurige waarde toe te laten -- dit is wat de setter
    // écht nuttig maakt.
    void setTargetTemperature(double value);

private:
    double targetTemperature_;
};
