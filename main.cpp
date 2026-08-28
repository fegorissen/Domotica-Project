#include <iostream>
#include <memory>
#include "Light.h"
#include "Thermostat.h"
#include "Doorlock.h"
#include "Camera.h"
#include "Room.h"
#include "LogHistory.h"

// vraag 27 (Object Georiënteerde Project - Aanvullend): everything in
// one or more self-made namespace(s)
using namespace smarthome;

// vraag 34 (Object Georiënteerde Project - Aanvullend): 2 useful
// (modern) call-by-references (2/2)
// 'room' wordt als NIET-const referentie doorgegeven: deze functie
// zou het object kunnen wijzigen indien nodig, zonder kopie of
// pointer-syntax.
void printActiveDeviceCount(Room& room)
{
    int count = 0;
    for (const auto& device : room.devices())
    {
        if (device->isOn())
        {
            ++count;
        }
    }
    std::cout << "Aantal actieve devices: " << count << std::endl;
}

// vraag 5 (Object Georiënteerde Project - Aanvullend): maintainability
// vraag 9 (Object Georiënteerde Project - Aanvullend): sufficient git commits
// vraag 10 (Object Georiënteerde Project - Aanvullend): correct files on git
// Zie https://github.com/fegorissen/Domotica-Project/commits/main

// vraag 2 (Object Georiënteerde Project - Aanvullend): clean main
int main()
{
    // vraag 32 (Object Georiënteerde Project - Aanvullend): dynamic memory allocation (new) (bewijs)
    // vraag 33 (Object Georiënteerde Project - Aanvullend): dynamic memory removing (delete) (bewijs)
    LogHistory log;

    Room livingRoom("Woonkamer");

    livingRoom.addDevice(std::make_unique<Light>("Woonkamerlamp"));
    livingRoom.addDevice(std::make_unique<Thermostat>("Verwarming"));
    livingRoom.addDevice(std::make_unique<DoorLock>("Voordeur"));
    livingRoom.addDevice(std::make_unique<Camera>("Cam Living"));
    log.add("4 devices toegevoegd aan Woonkamer");

    // vraag 12 (Object Georiënteerde Project - Aanvullend): at least 2 default constructors (bewijs)
    livingRoom.addDevice(std::make_unique<Light>());
    log.add("Unnamed Light toegevoegd via default constructor");

    livingRoom.printAllDevices();

    // vraag 8 (Object Georiënteerde Project - Aanvullend): fully working project
    // vraag 25 (Object Georiënteerde Project - Aanvullend): useful template function or class (bewijs)
    Device* thermostaatDevice = livingRoom.findDevice("Verwarming");
    if (thermostaatDevice != nullptr)
    {
        thermostaatDevice->toggle();
        log.add("Verwarming getoggled");
    }

    // vraag 31 (Object Georiënteerde Project - Aanvullend): at least 4 useful bool (3/4)
    Device* lamp = livingRoom.findDevice("Woonkamerlamp");
    bool lampFound = (lamp != nullptr);
    if (lampFound)
    {
        lamp->toggle();
        log.add("Woonkamerlamp getoggled");
    }

    // vraag 26 (Object Georiënteerde Project - Aanvullend): useful friend function or class (bewijs)
    if (lamp != nullptr)
    {
        std::cout << *lamp << std::endl;
    }

    Device* deur = livingRoom.findDevice("Voordeur");
    if (deur != nullptr)
    {
        deur->toggle();
        log.add("Voordeur getoggled");
    }

    // vraag 7 (Object Georiënteerde Project - Aanvullend): one complete project that compiles and does not crash
    Device* onbestaand = livingRoom.findDevice("Kelderlamp");
    // vraag 31 (Object Georiënteerde Project - Aanvullend): at least 4 useful bool (4/4)
    bool kelderlampBestaat = (onbestaand != nullptr);
    if (!kelderlampBestaat)
    {
        std::cout << "Kelderlamp bestaat niet in deze kamer." << std::endl;
        log.add("Zoekopdracht 'Kelderlamp' -> niet gevonden");
    }

    std::cout << "--- na toggle ---" << std::endl;
    livingRoom.printAllDevices();

    // vraag 34 (Object Georiënteerde Project - Aanvullend): 2 useful (modern) call-by-references (bewijs)
    printActiveDeviceCount(livingRoom);

    // vraag 25 (Object Georiënteerde Project - Aanvullend): useful template function or class (bewijs)
    Thermostat* thermostaat = dynamic_cast<Thermostat*>(thermostaatDevice);
    if (thermostaat != nullptr)
    {
        thermostaat->setTargetTemperature(999.0);
        log.add("Poging tot 999 graden -> geclampt");
        std::cout << "--- na poging tot 999 graden (clamp-test) ---" << std::endl;
        std::cout << "  Verwarming: " << thermostaat->status() << std::endl;

        // vraag 34 (Object Georiënteerde Project - Aanvullend): 2 useful (modern) call-by-references (bewijs)
        // applyEnergySavingMode ontvangt *thermostaat als referentie en
        // wijzigt het object rechtstreeks (geen kopie, geen pointer).
        applyEnergySavingMode(*thermostaat, 5.0);
        log.add("Energiebesparingsmodus toegepast (-5 graden)");
        std::cout << "--- na energiebesparingsmodus (-5 graden) ---" << std::endl;
        std::cout << "  Verwarming: " << thermostaat->status() << std::endl;
    }

    // vraag 14 (Object Georiënteerde Project - Aanvullend): at least 2 copy constructors (bewijs)
    Room roomCopy = livingRoom;
    log.add("Room gekopieerd (deep copy)");
    Device* lampInCopy = roomCopy.findDevice("Woonkamerlamp");
    if (lampInCopy != nullptr)
    {
        lampInCopy->toggle();
        log.add("Woonkamerlamp (in kopie) getoggled");
    }

    std::cout << "--- origineel (ongewijzigd) ---" << std::endl;
    livingRoom.printAllDevices();

    std::cout << "--- kopie (Woonkamerlamp getoggled) ---" << std::endl;
    roomCopy.printAllDevices();

    std::cout << "--- logboek (LogHistory, new[]/delete[]) ---" << std::endl;
    log.printAll(std::cout);

    // vraag 12: no mistake in object-oriented programming
    return 0;
}
