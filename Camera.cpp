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

void Camera::triggerMotion()
{
    motionDetected_ = true;
}
