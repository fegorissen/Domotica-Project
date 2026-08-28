#include "Camera.h"

namespace smarthome
{
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

    // vraag 36 (Object Georiënteerde Project - Aanvullend): useful container class
    std::string Camera::getTypeName() const
    {
        return "Camera";
    }

    std::unique_ptr<Device> Camera::clone() const
    {
        return std::make_unique<Camera>(*this);
    }

    void Camera::triggerMotion()
    {
        motionDetected_ = true;
    }
}
