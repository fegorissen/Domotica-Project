#include "DeviceFactory.h"
#include "Light.h"
#include "Thermostat.h"
#include "Doorlock.h"
#include "Camera.h"

namespace smarthome
{
std::unique_ptr<Device> createDeviceFromType(const std::string& typeName, const std::string& deviceName)
{
    if (typeName == "Light")
    {
        return std::make_unique<Light>(deviceName);
    }
    if (typeName == "Thermostat")
    {
        return std::make_unique<Thermostat>(deviceName);
    }
    if (typeName == "DoorLock")
    {
        return std::make_unique<DoorLock>(deviceName);
    }
    if (typeName == "Camera")
    {
        return std::make_unique<Camera>(deviceName);
    }
    return nullptr; // vraag 37: useful usage of nullptr -- onbekend type
}
}
