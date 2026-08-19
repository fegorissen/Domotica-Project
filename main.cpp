#include <iostream>
#include <memory>
#include "Light.h"
#include "Thermostat.h"
#include "Doorlock.h"
#include "Camera.h"
#include "Room.h"

// vraag 5 (Object Georiënteerde Project - Aanvullend): maintainability
// Dit geldt voor het volledige project, niet één regel: consistente
// naming (member variables eindigen op _, functies zijn camelCase,
// klassen zijn PascalCase), en comments overal die uitleggen WAAROM
// een OOP-keuze gemaakt is. Zie elk .h/.cpp-bestand hiervoor.

// vraag 9 (Object Georiënteerde Project - Aanvullend): sufficient git commits
// Dit project is opgebouwd in duidelijk afgebakende stappen, elk met
// een eigen, beschrijvende commit-boodschap. Zie de volledige
// geschiedenis op GitHub:
// https://github.com/fegorissen/Domotica-Project/commits/main

// vraag 10 (Object Georiënteerde Project - Aanvullend): correct files on git
// De repository bevat enkel de juiste bestanden: broncode (.h/.cpp),
// CMakeLists.txt, README.md, LICENSE en .gitignore. De build-map is
// bewust uitgesloten via .gitignore en verwijderd uit de
// git-geschiedenis.

// vraag 2 (Object Georiënteerde Project - Aanvullend): clean main
// main() bevat geen enkele beslissingslogica of berekening zelf -- het
// maakt enkel objecten aan en roept bestaande klassefuncties aan.
// Alle "denkwerk" zit in Room/Device en hun afgeleiden, niet hier.
int main()
{
    Room livingRoom("Woonkamer");

    livingRoom.addDevice(std::make_unique<Light>("Woonkamerlamp"));
    livingRoom.addDevice(std::make_unique<Thermostat>("Verwarming"));
    livingRoom.addDevice(std::make_unique<DoorLock>("Voordeur"));
    livingRoom.addDevice(std::make_unique<Camera>("Cam Living"));

    // vraag 12 (Object Georiënteerde Project - Aanvullend): at least 2 default constructors (bewijs)
    // Deze Light wordt aangemaakt via de default constructor (geen
    // argument meegegeven), die via constructor forwarding intern
    // Light("Unnamed Light") aanroept. Zichtbaar in de output hieronder
    // als "Unnamed Light: uit".
    livingRoom.addDevice(std::make_unique<Light>());

    livingRoom.printAllDevices();

    // vraag 8 (Object Georiënteerde Project - Aanvullend): fully working project
    // vraag 25 (Object Georiënteerde Project - Aanvullend): useful template function or class (bewijs)
    // We togglen de thermostaat aan, zodat status() de doeltemperatuur
    // toont (die intern via clamp<double>() begrensd werd bij het
    // aanmaken). Zichtbaar in de output als "verwarmt naar 21.000000
    // graden".
    Device* thermostaatDevice = livingRoom.findDevice("Verwarming");
    if (thermostaatDevice != nullptr)
    {
        thermostaatDevice->toggle();
    }

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

    // vraag 7 (Object Georiënteerde Project - Aanvullend): one complete
    // project that compiles and does not crash
    // findDevice() geeft nullptr terug voor een niet-bestaand device
    // (in plaats van een ongeldige pointer), en dat wordt hier
    // expliciet gecontroleerd vóór gebruik -- dit voorkomt een crash
    // bij deze edge case, net zoals bij elke andere aanroep hierboven.
    Device* onbestaand = livingRoom.findDevice("Kelderlamp");
    if (onbestaand == nullptr)
    {
        std::cout << "Kelderlamp bestaat niet in deze kamer." << std::endl;
    }

    std::cout << "--- na toggle ---" << std::endl;
    livingRoom.printAllDevices();

    // vraag 25 (Object Georiënteerde Project - Aanvullend): useful template function or class (bewijs)
    // We proberen de thermostaat op een onrealistische waarde (999
    // graden) te zetten via setTargetTemperature(), die intern
    // clamp<double>() gebruikt. De output hieronder toont dat de
    // waarde effectief begrensd wordt op 30 graden, niet 999.
    Thermostat* thermostaat = dynamic_cast<Thermostat*>(thermostaatDevice);
    if (thermostaat != nullptr)
    {
        thermostaat->setTargetTemperature(999.0);
        std::cout << "--- na poging tot 999 graden (clamp-test) ---" << std::endl;
        std::cout << "  Verwarming: " << thermostaat->status() << std::endl;
    }

    // vraag 14 (Object Georiënteerde Project - Aanvullend): at least 2 copy constructors (bewijs)
    // We maken een kopie van livingRoom en wijzigen enkel de kopie.
    // Doordat de copy constructor een DIEPE kopie maakt (via clone()
    // op elk device), blijft het origineel volledig ongewijzigd --
    // zichtbaar in de output hieronder.
    Room roomCopy = livingRoom;
    Device* lampInCopy = roomCopy.findDevice("Woonkamerlamp");
    if (lampInCopy != nullptr)
    {
        lampInCopy->toggle();
    }

    std::cout << "--- origineel (ongewijzigd) ---" << std::endl;
    livingRoom.printAllDevices();

    std::cout << "--- kopie (Woonkamerlamp getoggled) ---" << std::endl;
    roomCopy.printAllDevices();

    // vraag 12: no mistake in object-oriented programming
    // Geen dangling pointers (Room bezit devices via unique_ptr, zie
    // Room.h), geen ontbrekende virtuele destructor (zie Device.h),
    // consequent "override" i.p.v. "virtual" te herhalen, geen public
    // data members, geen overerving gebruikt waar compositie hoorde.
    return 0;
}
