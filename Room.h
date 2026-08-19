#pragma once
#include <string>
#include <vector>
#include <memory>
#include "Device.h"

// vraag 6 (Object Georiënteerde Project - Aanvullend): separate header files
// Elke klasse in dit project heeft zijn eigen .h/.cpp-paar: Device,
// Light, Thermostat, DoorLock, Camera en Room -- niets staat samen in
// één groot bestand.

// vraag 8: useful and correct object composition
// Room "has-a" verzameling Devices (via unique_ptr), geen inheritance.
class Room
{
public:
    // vraag 13 (Object Georiënteerde Project - Aanvullend): at least 2 parameterized constructors
    // Vereist een naam bij aanmaak, bv. Room livingRoom("Woonkamer").
    Room(std::string name);

    // vraag 12 (Object Georiënteerde Project - Aanvullend): at least 2 default constructors
    // vraag 17 (Object Georiënteerde Project - Aanvullend): constructor forwarding
    // Room() hergebruikt de parameterized constructor met een
    // standaardnaam, i.p.v. zelf opnieuw name_ te initialiseren.
    Room();

    // vraag 14 (Object Georiënteerde Project - Aanvullend): at least 2 copy constructors
    // Deze copy constructor is ECHT nodig en zelf geschreven (kan niet
    // = default zijn): devices_ is een vector<unique_ptr<Device>>, en
    // unique_ptr is niet kopieerbaar. We maken hier een DIEPE kopie
    // door voor elk device clone() aan te roepen, i.p.v. enkel de
    // pointers te kopiëren (wat sowieso niet zou compileren).
    Room(const Room& other);

    // vraag 19 (Object Georiënteerde Project - Aanvullend): useful usage of "this"
    // Copy-assignment operator: nodig om "roomB = roomA;" te
    // ondersteunen (in tegenstelling tot Room roomB(roomA), wat de
    // copy CONSTRUCTOR gebruikt). Zie Room.cpp voor waarom "this"
    // hier essentieel is.
    Room& operator=(const Room& other);

    // vraag 15 (Object Georiënteerde Project - Aanvullend): at least 2 destructors
    // Expliciet gedefinieerd (niet enkel = default) om aan te tonen
    // wanneer een Room precies opgeruimd wordt -- nuttig als bewijs
    // en als voorbeeld van hoe je destructor-gedrag kan uitbreiden
    // (bv. later loggen naar een bestand i.p.v. de console).
    ~Room();

    void addDevice(std::unique_ptr<Device> device);

    // vraag 20 (Object Georiënteerde Project - Aanvullend): useful member function
    // Lost een concreet, herbruikbaar probleem op: een device opzoeken
    // op naam zonder dat de aanroeper zelf door devices_ moet loopen.
    // Wordt drie keer hergebruikt in main.cpp (lamp, deur, en het
    // "niet-bestaand"-scenario), telkens met correcte nullptr-afhandeling.
    Device* findDevice(const std::string& name) const;

    void printAllDevices() const;

private:
    std::string name_;
    // vraag 8: useful and correct object composition
    // vraag 22 (Object Georiënteerde Project - Aanvullend): useful member variable
    // devices_ is de kern van deze klasse: zonder deze variabele zou
    // Room geen enkele van zijn functies (addDevice, findDevice,
    // printAllDevices) kunnen uitvoeren. Het is de eigenlijke data
    // die de compositie-relatie met Device mogelijk maakt.
    std::vector<std::unique_ptr<Device>> devices_;
};
