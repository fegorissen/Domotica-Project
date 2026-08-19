#pragma once
#include "Device.h"

class Camera : public Device
{
public:
    Camera(std::string name);

    void toggle() override;
    std::string status() const override;

    void triggerMotion();

private:
    bool motionDetected_ = false;
};
