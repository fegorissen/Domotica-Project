#pragma once
#include "Device.h"

namespace smarthome
{
// vraag 11: useful and correct virtual function
// override zorgt ervoor dat de compiler controleert of toggle()/
// status() écht een virtuele functie van Device overschrijven.
class DoorLock : public Device
{
public:
    DoorLock(std::string name);

    void toggle() override;
    std::string status() const override;
    std::unique_ptr<Device> clone() const override;
};
}
