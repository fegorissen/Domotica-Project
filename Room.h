#pragma once
#include <string>
#include <vector>
#include <memory>
#include "Device.h"

namespace smarthome
{
// vraag 6 (Object Georiënteerde Project - Aanvullend): separate header files
// Elke klasse in dit project heeft zijn eigen .h/.cpp-paar:
// Device, Light, Thermostat, DoorLock, Camera en Room.

// vraag 8: useful and correct object composition
// Room "has-a" verzameling Devices (via unique_ptr), geen
// inheritance.
class Room
{
public:
    // vraag 13 (Object Georiënteerde Project - Aanvullend): at least 2 parameterized constructors
    Room(std::string name);

    // vraag 12 (Object Georiënteerde Project - Aanvullend): at least 2 default constructors
    // vraag 17 (Object Georiënteerde Project - Aanvullend): constructor forwarding
    Room();

    // vraag 14 (Object Georiënteerde Project - Aanvullend): at least 2 copy constructors
    // Deze copy constructor is ECHT nodig en zelf geschreven (kan
    // niet = default zijn): devices_ is een
    // vector<unique_ptr<Device>>, en unique_ptr is niet
    // kopieerbaar. We maken hier een DIEPE kopie door voor elk
    // device clone() aan te roepen.
    Room(const Room& other);

    // vraag 19 (Object Georiënteerde Project - Aanvullend): useful usage of "this"
    Room& operator=(const Room& other);

    // vraag 15 (Object Georiënteerde Project - Aanvullend): at least 2 destructors
    ~Room();

    void addDevice(std::unique_ptr<Device> device);

    // vraag 20 (Object Georiënteerde Project - Aanvullend): useful member function
    Device* findDevice(const std::string& name) const;

    void printAllDevices() const;

private:
    std::string name_;
    // vraag 8: useful and correct object composition
    // vraag 22 (Object Georiënteerde Project - Aanvullend): useful member variable
    std::vector<std::unique_ptr<Device>> devices_;
};
}
