#pragma once
#include <string>

// vraag 4: useful and correct abstraction
// De abstractie is nuttig en correct omdat Device enkel de essentiële
// interface blootlegt (toggle(), status(), getName(), isOn()) zonder
// te tonen hoe een specifiek toestel zijn status precies samenstelt.
// Wie met een Device werkt, weet nooit hoe de interne implementatie
// van een Light of Camera eruitziet -- enkel dat elk Device een
// status() heeft. Dat is precies het doel van abstractie: het "wat"
// blootleggen, het "hoe" verbergen.
//
// vraag 9: useful and correct base class
// Device is een nuttige en correcte base class omdat het enkel bevat
// wat écht gemeenschappelijk is aan alle toestellen (naam, aan/uit-
// status, de interface), zonder implementatiedetails van specifieke
// toestellen op te leggen. Alle afgeleide klassen gebruiken deze basis
// zinvol, zonder overbodige of geforceerde overerving.
//
// vraag 10: useful and correct abstract base class
// Device is een échte abstracte base class: toggle() en status() zijn
// pure virtual (= 0), waardoor Device nooit rechtstreeks
// geïnstantieerd kan worden (Device d("test"); geeft een compile-
// fout). Dat is logisch, want een "generiek toestel" zonder concreet
// gedrag heeft geen betekenis -- enkel de afgeleide, concrete types
// (Light, Thermostat, ...) wel.
class Device
{
public:
    Device(std::string name);

    // vraag 11: useful and correct virtual function
    // De destructor is expliciet virtual, essentieel omdat objecten
    // via een Device-pointer beheerd worden (zie main.cpp/Room.cpp).
    // Zonder "virtual" zou bij vernietiging altijd enkel de opruiming
    // van Device zelf draaien, nooit die van het echte, afgeleide
    // type -- wat tot resource-problemen leidt.
    virtual ~Device() = default;

    // toggle() en status() zijn pure virtual: elke afgeleide klasse
    // moet ze zelf implementeren met "override" (zie Light.h,
    // Thermostat.h, Doorlock.h, Camera.h).
    virtual void toggle() = 0;
    virtual std::string status() const = 0;

    std::string getName() const;
    bool isOn() const;

protected:
    std::string name_;
    bool on_ = false;
};
