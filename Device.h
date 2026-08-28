#pragma once
#include <string>
#include <memory>
#include <ostream>

// vraag 27 (Object Georiënteerde Project - Aanvullend): everything in
// one or more self-made namespace(s)
namespace smarthome
{
// vraag 24 (Object Georiënteerde Project - Aanvullend): correct usage of inline function
inline std::string onOffText(bool on)
{
    return on ? "aan" : "uit";
}

// vraag 4: useful and correct abstraction
// vraag 9: useful and correct base class
// vraag 10: useful and correct abstract base class
class Device
{
public:
    // vraag 13 (Object Georiënteerde Project - Aanvullend): at least 2 parameterized constructors
    Device(std::string name);

    // vraag 11: useful and correct virtual function
    virtual ~Device() = default;

    virtual void toggle() = 0;
    virtual std::string status() const = 0;

    // vraag 36 (Object Georiënteerde Project - Aanvullend): useful container class
    // Elke afgeleide klasse geeft zijn eigen, leesbare typenaam
    // terug (bv. "Light", "Thermostat"). Wordt gebruikt in
    // Room::countDevicesByType() om devices per type te tellen in
    // een std::map.
    virtual std::string getTypeName() const = 0;

    // vraag 14 (Object Georiënteerde Project - Aanvullend): at least 2 copy constructors
    virtual std::unique_ptr<Device> clone() const = 0;

    std::string getName() const;

    // vraag 23 (Object Georiënteerde Project - Aanvullend): useful getters and setters for member variables
    // vraag 30 (Object Georiënteerde Project - Aanvullend): at least 4 useful const references for functions (1/5)
    void setName(const std::string& name);

    bool isOn() const;

    // vraag 20 (Object Georiënteerde Project - Aanvullend): useful member function
    unsigned char getId() const;

    // vraag 26 (Object Georiënteerde Project - Aanvullend): useful friend function or class
    // vraag 30 (Object Georiënteerde Project - Aanvullend): at least 4 useful const references for functions (2/5)
    friend std::ostream& operator<<(std::ostream& os, const Device& device);

    // vraag 4 (Object Georiënteerde Project - Aanvullend): correct protections
protected:
    std::string name_;
    // vraag 31 (Object Georiënteerde Project - Aanvullend): at least 4 useful bool (1/4)
    bool on_ = false;

private:
    // vraag 3 (Object Georiënteerde Project - Aanvullend): no globals, but statics if needed
    static unsigned char nextId_;
    unsigned char id_;
};
}
