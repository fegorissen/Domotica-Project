#include "House.h"
#include "DeviceFactory.h"
#include "json.hpp"
#include <fstream>
#include <iostream>

using json = nlohmann::json;

namespace smarthome
{
    House::House(std::string name)
        : name_(std::move(name))
    {
    }

    Room& House::addRoom(const std::string& roomName)
    {
        // std::map::operator[] maakt automatisch een nieuwe Room aan
        // (via zijn default constructor, vraag 12) als de sleutel nog
        // niet bestaat.
        rooms_[roomName] = Room(roomName);
        return rooms_[roomName];
    }

    Room* House::findRoom(const std::string& roomName)
    {
        auto it = rooms_.find(roomName);
        if (it == rooms_.end())
        {
            return nullptr;
        }
        return &it->second;
    }

    const Room* House::findRoom(const std::string& roomName) const
    {
        auto it = rooms_.find(roomName);
        if (it == rooms_.end())
        {
            return nullptr;
        }
        return &it->second;
    }

    std::map<std::string, Room>& House::rooms()
    {
        return rooms_;
    }

    const std::map<std::string, Room>& House::rooms() const
    {
        return rooms_;
    }

    int House::totalDeviceCount() const
    {
        int total = 0;
        for (const auto& pair : rooms_)
        {
            total += static_cast<int>(pair.second.devices().size());
        }
        return total;
    }

    // vraag 49 (Object Georiënteerde Project - Aanvullend): useful usage
    // of an external library (not Qt)
    // Slaat het HELE huis op als één JSON-bestand: een object met een
    // array van kamers, elk met hun eigen devices-array.
    void House::saveToFile(const std::string& path) const
    {
        json j;
        j["house"] = name_;
        j["rooms"] = json::array();

        for (const auto& pair : rooms_)
        {
            const Room& room = pair.second;
            json roomJson;
            roomJson["name"] = room.getName();
            roomJson["devices"] = json::array();

            for (const auto& device : room.devices())
            {
                json deviceJson;
                deviceJson["type"] = device->getTypeName();
                deviceJson["name"] = device->getName();
                deviceJson["on"] = device->isOn();
                roomJson["devices"].push_back(deviceJson);
            }

            j["rooms"].push_back(roomJson);
        }

        std::ofstream out(path);
        if (!out.is_open())
        {
            std::cout << "Kon bestand niet openen om op te slaan: " << path << std::endl;
            return;
        }
        out << j.dump(2);
    }

    void House::loadFromFile(const std::string& path)
    {
        std::ifstream in(path);
        if (!in.is_open())
        {
            std::cout << "Kon bestand niet openen om te laden: " << path << std::endl;
            return;
        }

        json j;
        in >> j;

        rooms_.clear();

        for (const auto& roomJson : j["rooms"])
        {
            std::string roomName = roomJson["name"];
            Room& room = addRoom(roomName);

            for (const auto& deviceJson : roomJson["devices"])
            {
                std::string typeName = deviceJson["type"];
                std::string deviceName = deviceJson["name"];
                bool wasOn = deviceJson["on"];

                auto device = createDeviceFromType(typeName, deviceName);
                if (device == nullptr)
                {
                    continue;
                }
                if (wasOn != device->isOn())
                {
                    device->toggle();
                }
                room.addDevice(std::move(device));
            }
        }
    }

    const std::string& House::getName() const
    {
        return name_;
    }
}
