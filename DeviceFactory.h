#pragma once
#include <memory>
#include <string>
#include "Device.h"

namespace smarthome
{
// vraag 38 (Object Georiënteerde Project - Aanvullend): useful usage
// of (modern) file-I/O
// Bouwt een device van het juiste concrete type op basis van een
// typenaam-string (bv. "Light" -> maakt een Light-object). Wordt
// gebruikt door Room::loadFromFile om de polymorfe objecten
// opnieuw te reconstrueren vanuit tekst.
std::unique_ptr<Device> createDeviceFromType(const std::string& typeName, const std::string& deviceName);
}
