#include <iostream>
#include <memory>
#include "Light.h"
#include "Thermostat.h"
#include "Doorlock.h"
#include "Camera.h"
#include "Room.h"

// vraag 2 (Object Georiënteerde Project - Aanvullend): clean main
// main() bevat geen enkele beslissingslogica of berekening zelf -- het
// maakt enkel objecten aan (Room, devices) en roept bestaande
// klassefuncties aan (addDevice, findDevice, toggle, printAllDevices).
// Alle "denkwerk" zit in Room/Device en hun afgeleiden, niet in main().

// vraag 5 (Object Georiënteerde Project - Aanvullend): maintainability
// Doorheen het volledige project wordt één consistente stijl gevolgd:
//  - Member variables eindigen steeds op een underscore (name_, on_,
//    id_, devices_, motionDetected_, ...).
//  - Functienamen zijn camelCase en beschrijvend (getName, isOn,
//    addDevice, findDevice, printAllDevices, triggerMotion).
//  - Klassenamen zijn PascalCase (Device, Light, Thermostat, Room).
//  - Elke klasse/header bevat comments die uitleggen WAAROM een
//    bepaalde OOP-keuze gemaakt is, niet enkel wat de code doet.
//  - Consistente indentatie en accolade-stijl in alle bestanden.

// vraag 12: no mistake in object-oriented programming (deel 2)
// Overzicht van bewust vermeden OOP-valkuilen doorheen het project:
//  - Geen dangling pointers: Room bezit zijn devices via unique_ptr
//    (zie Room.h) in plaats van rauwe pointers naar lokale
//    variabelen, die ongeldig zouden worden zodra die variabelen uit
//    scope gaan.
//  - Geen crash bij een niet-bestaand device: findDevice() geeft
//    nullptr terug (zie Room.cpp), en dat wordt hieronder altijd
//    expliciet gecontroleerd vóór gebruik.
//  - Geen ontbrekende virtuele destructor: Device::~Device() is
//    virtual (zie Device.h), essentieel omdat objecten via een
//    Device-pointer beheerd worden.
//  - Consequent "override" i.p.v. "virtual" te herhalen in elke
//    afgeleide klasse (zie Light.h, Thermostat.h, Doorlock.h,
//    Camera.h) -- de compiler controleert zo mee of de signatuur
//    klopt.
//  - Geen public data members: alle velden zijn protected/private met
//    gecontroleerde toegang via functies (zie Device.h, Camera.h).
//  - Geen overerving gebruikt waar compositie hoorde: Room erft niet
//    van Device, het bevat Devices als lid (zie Room.h).

int main()
{
    Room livingRoom("Woonkamer");

    livingRoom.addDevice(std::make_unique<Light>("Woonkamerlamp"));
    livingRoom.addDevice(std::make_unique<Thermostat>("Verwarming"));
    livingRoom.addDevice(std::make_unique<DoorLock>("Voordeur"));
    livingRoom.addDevice(std::make_unique<Camera>("Cam Living"));

    livingRoom.printAllDevices();

    Device* lamp = livingRoom.findDevice("Woonkamerlamp");
    if (lamp != nullptr)
    {
        lamp->toggle();
    }

    Device* deur = livingRoom.findDevice("Voordeur");
    if (deur != nullptr)
    {
        deur->toggle();
    }

    Device* onbestaand = livingRoom.findDevice("Kelderlamp");
    if (onbestaand == nullptr)
    {
        std::cout << "Kelderlamp bestaat niet in deze kamer." << std::endl;
    }

    std::cout << "--- na toggle ---" << std::endl;
    livingRoom.printAllDevices();

    return 0;
}
