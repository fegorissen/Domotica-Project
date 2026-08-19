#include <iostream>
#include <memory>
#include "Light.h"
#include "Thermostat.h"
#include "DoorLock.h"
#include "Camera.h"
#include "Room.h"

int main()
{
    Room livingRoom("Woonkamer");

    livingRoom.addDevice(std::make_unique<Light>("Woonkamerlamp"));
    livingRoom.addDevice(std::make_unique<Thermostat>("Verwarming"));
    livingRoom.addDevice(std::make_unique<DoorLock>("Voordeur"));
    livingRoom.addDevice(std::make_unique<Camera>("Cam Living"));

    livingRoom.printAllDevices();

    Device* lamp = livingRoom.findDevice("Woonkamerlamp");
    if (lamp != nullptr)
    {
        lamp->toggle();
    }

    Device* deur = livingRoom.findDevice("Voordeur");
    if (deur != nullptr)
    {
        deur->toggle();
    }

    Device* onbestaand = livingRoom.findDevice("Kelderlamp");
    if (onbestaand == nullptr)
    {
        std::cout << "Kelderlamp bestaat niet in deze kamer." << std::endl;
    }

    std::cout << "--- na toggle ---" << std::endl;
    livingRoom.printAllDevices();

    return 0;
}
