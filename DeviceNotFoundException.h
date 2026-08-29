#pragma once
#include <stdexcept>
#include <string>

namespace smarthome
{
// vraag 39 (Object Georiënteerde Project - Aanvullend): useful
// exception handling
// Eigen, betekenisvol exception-type i.p.v. een generieke
// std::runtime_error overal -- een catch-block kan hierdoor
// specifiek reageren op "device niet gevonden", los van andere
// mogelijke fouten (bv. file-I/O fouten).
class DeviceNotFoundException : public std::runtime_error
{
public:
    explicit DeviceNotFoundException(const std::string& deviceName)
        : std::runtime_error("Device niet gevonden: " + deviceName)
    {
    }
};
}
