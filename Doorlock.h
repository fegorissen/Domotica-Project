#pragma once
#include "Device.h"

namespace smarthome
{
// vraag 11: useful and correct virtual function
class DoorLock : public Device
{
public:
    DoorLock(std::string name);

    void toggle() override;
    std::string status() const override;
    std::string getTypeName() const override;
    std::unique_ptr<Device> clone() const override;
};
}
