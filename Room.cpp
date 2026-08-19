#include "Room.h"
#include <iostream>
#include <utility>

Room::Room(std::string name)
    : name_(name)
{
}

void Room::addDevice(std::unique_ptr<Device> device)
{
    devices_.push_back(std::move(device));
}

// vraag 12: no mistake in object-oriented programming (deel 1)
// findDevice() geeft nullptr terug als het device niet bestaat, in
// plaats van te crashen of een ongeldige pointer terug te geven. Dit
// voorkomt undefined behaviour: elke aanroeper (zie main.cpp)
// controleert expliciet op nullptr vóór gebruik. Dit is ook een
// voorbeeld van "useful usage of nullptr": de standaard C++-manier
// om "niet gevonden" aan te geven bij een functie die een pointer
// teruggeeft.
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

// vraag 7: useful and correct polymorphism
// Polymorfisme is hier nuttig en correct toegepast omdat device->
// status() telkens het juiste, type-specifieke resultaat teruggeeft
// (Light/Thermostat/DoorLock/Camera), zonder dat Room ooit weet welk
// concreet type er precies in de vector zit. Welke implementatie van
// status() effectief draait, wordt pas tijdens uitvoering bepaald via
// dynamic dispatch -- dankzij de virtuele functies in Device. Dat
// maakt de code flexibel en uitbreidbaar: een nieuw type Device
// toevoegen vereist geen enkele wijziging aan deze functie.
void Room::printAllDevices() const
{
    std::cout << "Kamer: " << name_ << std::endl;
    for (const auto& device : devices_)
    {
        std::cout << "  " << device->getName() << ": " << device->status() << std::endl;
    }
}
