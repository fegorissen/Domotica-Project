#include "Room.h"
#include <iostream>
#include <utility>

namespace smarthome
{
    Room::Room(std::string name)
        : name_(name)
    {
    }

    Room::Room()
        : Room("Unnamed Room")
    {
    }

    Room::Room(const Room& other)
        : name_(other.name_)
    {
        for (const auto& device : other.devices_)
        {
            devices_.push_back(device->clone());
        }
    }

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

    Room::~Room()
    {
        std::cout << "Kamer '" << name_ << "' wordt opgeruimd." << std::endl;
    }

    void Room::addDevice(std::unique_ptr<Device> device)
    {
        devices_.push_back(std::move(device));
    }

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

    void Room::printAllDevices() const
    {
        std::cout << "Kamer: " << name_ << std::endl;
        for (const auto& device : devices_)
        {
            std::cout << "  " << device->getName() << ": " << device->status() << std::endl;
        }
    }

    const std::vector<std::unique_ptr<Device>>& Room::devices() const
    {
        return devices_;
    }

    // vraag 35 (Object Georiënteerde Project - Aanvullend): useful string class usage
    int Room::countDevicesContaining(const std::string& searchTerm) const
    {
        int count = 0;
        for (const auto& device : devices_)
        {
            if (device->getName().find(searchTerm) != std::string::npos)
            {
                ++count;
            }
        }
        return count;
    }

    // vraag 36 (Object Georiënteerde Project - Aanvullend): useful container class
    std::map<std::string, int> Room::countDevicesByType() const
    {
        std::map<std::string, int> counts;
        for (const auto& device : devices_)
        {
            ++counts[device->getTypeName()];
        }
        return counts;
    }
}
