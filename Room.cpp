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
