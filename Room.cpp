#include "Room.h"
#include <iostream>
#include <utility>

namespace smarthome
{
    Room::Room(std::string name)
        : name_(name)
    {
    }

    // vraag 17 (Object Georiënteerde Project - Aanvullend): constructor forwarding
    Room::Room()
        : Room("Unnamed Room")
    {
    }

    // vraag 14 (Object Georiënteerde Project - Aanvullend): at least 2 copy constructors
    // vraag 18 (Object Georiënteerde Project - Aanvullend): useful proven (dynamic) polymorphism
    // Diepe kopie: voor elk device in 'other' wordt clone()
    // aangeroepen, wat een volledig nieuw, onafhankelijk
    // Device-object maakt van het juiste, concrete type.
    Room::Room(const Room& other)
        : name_(other.name_)
    {
        for (const auto& device : other.devices_)
        {
            devices_.push_back(device->clone());
        }
    }

    // vraag 19 (Object Georiënteerde Project - Aanvullend): useful usage of "this"
    // De check "if (this == &other)" vergelijkt het geheugenadres van
    // het huidige object met het adres van de parameter -- dit kan
    // ENKEL met "this". Zonder deze check zou "room = room;" tot
    // dataverlies leiden.
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
    void Room::printAllDevices() const
    {
        std::cout << "Kamer: " << name_ << std::endl;
        for (const auto& device : devices_)
        {
            std::cout << "  " << device->getName() << ": " << device->status() << std::endl;
        }
    }
}
