#include "Device.h"

Device::Device(std::string name)
    : name_(name)
{
}

std::string Device::getName() const
{
    return name_;
}

bool Device::isOn() const
{
    return on_;
}
