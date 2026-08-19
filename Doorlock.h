#pragma once
#include "Device.h"

class DoorLock : public Device
{
public:
    DoorLock(std::string name);

    void toggle() override;
    std::string status() const override;
};
