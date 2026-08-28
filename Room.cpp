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
    Room::Room(const Room& other)
        : name_(other.name_)
    {
        // vraag 29 (Object Georiënteerde Project - Aanvullend): at least
        // 4 useful const references for variables (1/4)
        // 'device' is een const reference: geen kopie van de
        // unique_ptr (die is sowieso niet kopieerbaar), en de lus kan
        // 'other' niet per ongeluk wijzigen.
        for (const auto& device : other.devices_)
        {
            devices_.push_back(device->clone());
        }
    }

    // vraag 19 (Object Georiënteerde Project - Aanvullend): useful usage of "this"
    Room& Room::operator=(const Room& other)
    {
        if (this == &other)
        {
            return *this;
        }

        name_ = other.name_;
        devices_.clear();
        // vraag 29 (Object Georiënteerde Project - Aanvullend): at least
        // 4 useful const references for variables (2/4)
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
        // vraag 29 (Object Georiënteerde Project - Aanvullend): at least
        // 4 useful const references for variables (3/4)
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
        // vraag 29 (Object Georiënteerde Project - Aanvullend): at least
        // 4 useful const references for variables (4/4)
        for (const auto& device : devices_)
        {
            std::cout << "  " << device->getName() << ": " << device->status() << std::endl;
        }
    }
}
