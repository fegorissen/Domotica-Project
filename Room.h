#pragma once
#include <string>
#include <vector>
#include <map>
#include <memory>
#include "Device.h"

namespace smarthome
{
// vraag 6 (Object Georiënteerde Project - Aanvullend): separate header files
// vraag 8: useful and correct object composition
class Room
{
public:
    // vraag 13 (Object Georiënteerde Project - Aanvullend): at least 2 parameterized constructors
    Room(std::string name);

    // vraag 12 (Object Georiënteerde Project - Aanvullend): at least 2 default constructors
    // vraag 17 (Object Georiënteerde Project - Aanvullend): constructor forwarding
    Room();

    // vraag 14 (Object Georiënteerde Project - Aanvullend): at least 2 copy constructors
    // vraag 30 (Object Georiënteerde Project - Aanvullend): at least 4 useful const references for functions (3/5)
    Room(const Room& other);

    // vraag 19 (Object Georiënteerde Project - Aanvullend): useful usage of "this"
    // vraag 30 (Object Georiënteerde Project - Aanvullend): at least 4 useful const references for functions (4/5)
    Room& operator=(const Room& other);

    // vraag 15 (Object Georiënteerde Project - Aanvullend): at least 2 destructors
    ~Room();

    void addDevice(std::unique_ptr<Device> device);

    // vraag 20 (Object Georiënteerde Project - Aanvullend): useful member function
    // vraag 30 (Object Georiënteerde Project - Aanvullend): at least 4 useful const references for functions (5/5)
    Device* findDevice(const std::string& name) const;

    void printAllDevices() const;

    // vraag 34 (Object Georiënteerde Project - Aanvullend): 2 useful (modern) call-by-references (2/2)
    const std::vector<std::unique_ptr<Device>>& devices() const;

    // vraag 35 (Object Georiënteerde Project - Aanvullend): useful string class usage
    int countDevicesContaining(const std::string& searchTerm) const;

    // vraag 36 (Object Georiënteerde Project - Aanvullend): useful container class
    // std::map houdt sleutel-waarde paren bij (typenaam -> aantal),
    // in tegenstelling tot de eenvoudige, geordende lijst van
    // std::vector. Nuttig om snel op te zoeken hoeveel devices van
    // elk type in deze kamer staan.
    std::map<std::string, int> countDevicesByType() const;

private:
    std::string name_;
    // vraag 8: useful and correct object composition
    // vraag 22 (Object Georiënteerde Project - Aanvullend): useful member variable
    std::vector<std::unique_ptr<Device>> devices_;
};
}
