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
    std::string getTypeName() const override;
    std::unique_ptr<Device> clone() const override;

    void triggerMotion();

private:
    // vraag 5: useful and correct encapsulation
    // vraag 31 (Object Georiënteerde Project - Aanvullend): at least 4 useful bool (2/4)
    bool motionDetected_ = false;
};
}
