#include "Room.h"
#include "DeviceFactory.h"
#include "DeviceNotFoundException.h"
#include "Thermostat.h"
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

    // vraag 17 (Object Georiënteerde Project - Aanvullend): constructor forwarding
    Room::Room()
        : Room("Unnamed Room")
    {
    }

    // vraag 14 (Object Georiënteerde Project - Aanvullend): at least 2 copy constructors
    // vraag 18 (Object Georiënteerde Project - Aanvullend): useful proven (dynamic) polymorphism
    // Diepe kopie: voor elk device in 'other' wordt clone() aangeroepen,
    // wat een volledig nieuw, onafhankelijk Device-object maakt van het
    // juiste, concrete type (Light/Thermostat/...).
    Room::Room(const Room& other)
        : name_(other.name_)
    {
        // vraag 29 (Object Georiënteerde Project - Aanvullend): at least 4 useful const references for variables (1/4)
        for (const auto& device : other.devices_)
        {
            devices_.push_back(device->clone());
        }
    }

    // vraag 19 (Object Georiënteerde Project - Aanvullend): useful usage of "this"
    // De check "if (this == &other)" vergelijkt het GEHEUGENADRES van het
    // huidige object met het adres van de parameter -- dit kan ENKEL met
    // "this". Zonder deze check zou "room = room;" tot dataverlies leiden.
    Room& Room::operator=(const Room& other)
    {
        if (this == &other)
        {
            return *this;
        }

        name_ = other.name_;
        devices_.clear();
        // vraag 29 (Object Georiënteerde Project - Aanvullend): at least 4 useful const references for variables (2/4)
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

    // vraag 37 (Object Georiënteerde Project - Aanvullend): useful usage of nullptr
    // Geeft nullptr terug als er geen device met deze naam bestaat --
    // de standaard, type-safe C++-manier om "niet gevonden" aan te
    // geven bij een functie die een pointer teruggeeft.
    Device* Room::findDevice(const std::string& name) const
    {
        // vraag 29 (Object Georiënteerde Project - Aanvullend): at least 4 useful const references for variables (3/4)
        for (const auto& device : devices_)
        {
            if (device->getName() == name)
            {
                return device.get();
            }
        }
        return nullptr;
    }

    // vraag 39 (Object Georiënteerde Project - Aanvullend): useful exception handling
    Device& Room::getDeviceOrThrow(const std::string& name) const
    {
        Device* device = findDevice(name);
        if (device == nullptr)
        {
            throw DeviceNotFoundException(name);
        }
        return *device;
    }

    // vraag 18 (Object Georiënteerde Project - Aanvullend): useful proven (dynamic) polymorphism
    // device->status() geeft hier telkens het juiste, type-specifieke
    // resultaat terug, zonder dat Room ooit weet welk concreet type er
    // precies in de vector zit.
    void Room::printAllDevices() const
    {
        std::cout << "Kamer: " << name_ << std::endl;
        // vraag 29 (Object Georiënteerde Project - Aanvullend): at least 4 useful const references for variables (4/4)
        for (const auto& device : devices_)
        {
            std::cout << "  " << device->getName() << ": " << device->status() << std::endl;
        }
    }

    // vraag 34 (Object Georiënteerde Project - Aanvullend): 2 useful (modern) call-by-references (2/2)
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
            // find() zoekt 'searchTerm' ergens in de naam en geeft de
            // positie terug, of std::string::npos als het er niet in
            // staat.
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

    // vraag 40 (Object Georiënteerde Project - Aanvullend): useful usage of lambda function
    int Room::countDevicesIf(const std::function<bool(const Device&)>& predicate) const
    {
        int count = 0;
        for (const auto& device : devices_)
        {
            if (predicate(*device))
            {
                ++count;
            }
        }
        return count;
    }

    // vraag 38 (Object Georiënteerde Project - Aanvullend): useful usage of (modern) file-I/O
    // Fix #1: Thermostat doeltemperatuur gaat verloren bij save/load.
    // We voegen een vierde, optioneel veld toe aan het formaat:
    // "type|naam|aan-uit|extra". Voor een Thermostat bevat 'extra' de
    // doeltemperatuur; voor andere types blijft het gewoon "0" (niet
    // gebruikt, maar houdt het formaat consistent en makkelijk uit te
    // breiden voor toekomstige devices).
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
            std::string extra = "0";
            if (const auto* thermostat = dynamic_cast<const Thermostat*>(device.get()))
            {
                extra = std::to_string(thermostat->getTargetTemperature());
            }

            out << device->getTypeName() << '|' << device->getName() << '|'
                << (device->isOn() ? 1 : 0) << '|' << extra << '\n';
        }
    }

    // vraag 38 (Object Georiënteerde Project - Aanvullend): useful usage of (modern) file-I/O
    // Fix #1 (vervolg): bij het laden lezen we het vierde veld nu ook
    // in, en passen het toe via setTargetTemperature() als het device
    // een Thermostat blijkt te zijn.
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
            std::string typeName, deviceName, onStr, extraStr;
            std::getline(iss, typeName, '|');
            std::getline(iss, deviceName, '|');
            std::getline(iss, onStr, '|');
            std::getline(iss, extraStr, '|');

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

            if (auto* thermostat = dynamic_cast<Thermostat*>(device.get()))
            {
                if (!extraStr.empty())
                {
                    thermostat->setTargetTemperature(std::stod(extraStr));
                }
            }

            devices_.push_back(std::move(device));
        }
    }
}
