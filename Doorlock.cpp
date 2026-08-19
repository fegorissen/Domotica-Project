#include "DoorLock.h"

DoorLock::DoorLock(std::string name)
    : Device(name)
{
}

void DoorLock::toggle()
{
    on_ = !on_;
}

std::string DoorLock::status() const
{
    if (on_)
        return "vergrendeld";
    else
        return "ontgrendeld";
}
