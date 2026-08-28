#pragma once
#include "Device.h"

namespace smarthome
{
class Camera : public Device
{
public:
    Camera(std::string name);

    void toggle() override;
    std::string status() const override;
    std::unique_ptr<Device> clone() const override;

    void triggerMotion();

private:
    // vraag 5: useful and correct encapsulation
    // motionDetected_ is private: enkel bereikbaar via
    // triggerMotion() en indirect via status().
    bool motionDetected_ = false;
};
}
