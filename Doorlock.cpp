#include "Doorlock.h"

namespace smarthome
{
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

    // vraag 36 (Object Georiënteerde Project - Aanvullend): useful container class
    std::string DoorLock::getTypeName() const
    {
        return "DoorLock";
    }

    std::unique_ptr<Device> DoorLock::clone() const
    {
        return std::make_unique<DoorLock>(*this);
    }
}
