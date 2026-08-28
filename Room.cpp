#include "Room.h"
#include "DeviceFactory.h"
#include <iostream>
#include <fstream>
#include <sstream>
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

    std::map<std::string, int> Room::countDevicesByType() const
    {
        std::map<std::string, int> counts;
        for (const auto& device : devices_)
        {
            ++counts[device->getTypeName()];
        }
        return counts;
    }

    // vraag 38 (Object Georiënteerde Project - Aanvullend): useful usage of (modern) file-I/O
    void Room::saveToFile(const std::string& path) const
    {
        std::ofstream out(path);
        if (!out.is_open())
        {
            std::cout << "Kon bestand niet openen om op te slaan: " << path << std::endl;
            return;
        }

        for (const auto& device : devices_)
        {
            out << device->getTypeName() << '|' << device->getName() << '|'
                << (device->isOn() ? 1 : 0) << '\n';
        }
    }

    // vraag 38 (Object Georiënteerde Project - Aanvullend): useful usage of (modern) file-I/O
    void Room::loadFromFile(const std::string& path)
    {
        std::ifstream in(path);
        if (!in.is_open())
        {
            std::cout << "Kon bestand niet openen om te laden: " << path << std::endl;
            return;
        }

        devices_.clear();

        std::string line;
        while (std::getline(in, line))
        {
            if (line.empty())
            {
                continue;
            }

            std::istringstream iss(line);
            std::string typeName, deviceName, onStr;
            std::getline(iss, typeName, '|');
            std::getline(iss, deviceName, '|');
            std::getline(iss, onStr, '|');

            auto device = createDeviceFromType(typeName, deviceName);
            if (device == nullptr)
            {
                continue;
            }

            bool wasOn = (onStr == "1");
            if (wasOn != device->isOn())
            {
                device->toggle();
            }

            devices_.push_back(std::move(device));
        }
    }
}
