#include "Device.h"

namespace smarthome
{
// vraag 3 (Object Georiënteerde Project - Aanvullend): no globals, but statics if needed
// De definitie/initialisatie van de static member. Dit is de
// ENIGE plek in het hele programma waar deze teller bestaat --
// gedeeld door alle Device-objecten.
unsigned char Device::nextId_ = 1;

// vraag 16 (Object Georiënteerde Project - Aanvullend): member initialization in constructors
Device::Device(std::string name)
    : name_(name), id_(nextId_++)
{
}

std::string Device::getName() const
{
    return name_;
}

// vraag 23 (Object Georiënteerde Project - Aanvullend): useful getters and setters for member variables
void Device::setName(const std::string& name)
{
    if (!name.empty())
    {
        name_ = name;
    }
}

bool Device::isOn() const
{
    return on_;
}

unsigned char Device::getId() const
{
    return id_;
}

// vraag 26 (Object Georiënteerde Project - Aanvullend): useful friend function or class
std::ostream& operator<<(std::ostream& os, const Device& device)
{
    os << "[#" << static_cast<int>(device.id_) << "] " << device.name_
       << ": " << device.status();
    return os;
}
}
