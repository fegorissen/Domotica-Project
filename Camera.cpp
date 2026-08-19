#include "Camera.h"

Camera::Camera(std::string name)
    : Device(name)
{
}

void Camera::toggle()
{
    on_ = !on_;
}

std::string Camera::status() const
{
    if (!on_)
        return "uitgeschakeld";

    if (motionDetected_)
        return "opname (beweging gedetecteerd!)";
    else
        return "opname (rustig)";
}

std::unique_ptr<Device> Camera::clone() const
{
    return std::make_unique<Camera>(*this);
}

void Camera::triggerMotion()
{
    motionDetected_ = true;
}
