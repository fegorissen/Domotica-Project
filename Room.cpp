#include "Room.h"
#include <iostream>
#include <utility>

Room::Room(std::string name)
    : name_(name)
{
}

// vraag 17 (Object Georiënteerde Project - Aanvullend): constructor forwarding
// Room() hergebruikt de bestaande parameterized constructor met een
// standaardnaam, i.p.v. de initialisatie hier te herhalen.
Room::Room()
    : Room("Unnamed Room")
{
}

// vraag 14 (Object Georiënteerde Project - Aanvullend): at least 2 copy constructors
// vraag 18 (Object Georiënteerde Project - Aanvullend): useful proven (dynamic) polymorphism
// Diepe kopie: voor elk device in 'other' wordt clone() aangeroepen,
// wat een volledig nieuw, onafhankelijk Device-object maakt van het
// juiste, concrete type (Light/Thermostat/...). Dit BEWIJST dynamisch
// polymorfisme: clone() wordt hier aangeroepen op een unique_ptr<Device>
// zonder dat Room weet welk concreet type erachter zit, en toch krijgt
// elk device zijn eigen, correcte kopie.
Room::Room(const Room& other)
    : name_(other.name_)
{
    for (const auto& device : other.devices_)
    {
        devices_.push_back(device->clone());
    }
}

// vraag 19 (Object Georiënteerde Project - Aanvullend): useful usage of "this"
// De check "if (this == &other)" vergelijkt het GEHEUGENADRES van het
// huidige object met het adres van de parameter -- dit kan ENKEL met
// "this", er bestaat geen alternatief. Zonder deze check zou
// "room = room;" (zelftoewijzing) devices_ eerst leegmaken vóór het
// "nieuwe" (in werkelijkheid hetzelfde) object gekopieerd wordt, wat
// tot dataverlies leidt. De code werkt dus letterlijk niet correct
// zonder "this".
Room& Room::operator=(const Room& other)
{
    if (this == &other)
    {
        return *this;
    }

    name_ = other.name_;
    devices_.clear();
    for (const auto& device : other.devices_)
    {
        devices_.push_back(device->clone());
    }

    return *this;
}

// vraag 15 (Object Georiënteerde Project - Aanvullend): at least 2 destructors
// Toont expliciet wanneer een Room-object precies vernietigd wordt --
// nuttig om het levensverloop van objecten te kunnen volgen, en een
// duidelijk, herkenbaar voorbeeld naast de virtuele destructor in
// Device.
Room::~Room()
{
    std::cout << "Kamer '" << name_ << "' wordt opgeruimd." << std::endl;
}

void Room::addDevice(std::unique_ptr<Device> device)
{
    devices_.push_back(std::move(device));
}

// vraag 20 (Object Georiënteerde Project - Aanvullend): useful member function
Device* Room::findDevice(const std::string& name) const
{
    for (const auto& device : devices_)
    {
        if (device->getName() == name)
        {
            return device.get();
        }
    }
    return nullptr;
}

// vraag 18 (Object Georiënteerde Project - Aanvullend): useful proven (dynamic) polymorphism
// device->status() geeft hier telkens het juiste, type-specifieke
// resultaat terug (Light/Thermostat/DoorLock/Camera), zonder dat Room
// ooit weet welk concreet type er precies in de vector zit. Welke
// implementatie effectief draait, wordt pas tijdens uitvoering
// bepaald via dynamic dispatch.
void Room::printAllDevices() const
{
    std::cout << "Kamer: " << name_ << std::endl;
    for (const auto& device : devices_)
    {
        std::cout << "  " << device->getName() << ": " << device->status() << std::endl;
    }
}
