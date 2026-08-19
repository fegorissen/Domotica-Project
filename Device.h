#pragma once
#include <string>

// vraag 4: useful and correct abstraction
// vraag 9: useful and correct base class
// vraag 10: useful and correct abstract base class
// Device legt de gemeenschappelijke interface vast (naam, aan/uit,
// toggle, status) voor elk toestel, zonder de details van een
// specifiek toestel te tonen. Doordat toggle()/status() pure virtual
// zijn (= 0), kan Device nooit rechtstreeks geïnstantieerd worden.
//
// vraag 4 (Object Georiënteerde Project - Aanvullend): correct protections
// Drie niveaus worden hier bewust en correct gebruikt:
//  - public: enkel wat de buitenwereld moet kunnen aanroepen
//    (constructor, toggle(), status(), getName(), isOn(), getId()).
//  - protected: name_ en on_ zijn nodig in de afgeleide klassen
//    (Light/Thermostat/DoorLock/Camera gebruiken ze rechtstreeks in
//    hun eigen toggle()), maar mogen niet van buiten de klasse-
//    hiërarchie aangepast worden.
//  - private: nextId_ en id_ zijn interne implementatiedetails die
//    zelfs afgeleide klassen niet nodig hebben en dus niet mogen
//    aanraken -- enkel Device zelf beheert de ID-toekenning.
class Device
{
public:
    Device(std::string name);

    // vraag 11: useful and correct virtual function
    // Virtueel, want objecten worden later via een Device-pointer
    // gebruikt (zie main.cpp) en moeten correct opgeruimd worden.
    virtual ~Device() = default;

    virtual void toggle() = 0;
    virtual std::string status() const = 0;

    std::string getName() const;
    bool isOn() const;

    // vraag 20 (Object Georiënteerde Project - Aanvullend): useful member function
    // Geeft het unieke ID van dit device terug, toegekend bij aanmaak.
    unsigned char getId() const;

protected:
    std::string name_;
    bool on_ = false;

private:
    // vraag 3 (Object Georiënteerde Project - Aanvullend): no globals, but statics if needed
    // nextId_ is een static member: gedeeld door alle Device-objecten
    // (er bestaat maar één "teller" voor de hele klasse), maar netjes
    // ingekapseld binnen Device zelf -- geen globale variabele die
    // van overal in het programma rechtstreeks aanpasbaar zou zijn.
    // Elke nieuwe Device krijgt hiermee automatisch een uniek ID.
    static unsigned char nextId_;
    unsigned char id_;
};
