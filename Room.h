#pragma once
#include <string>
#include <vector>
#include <memory>
#include "Device.h"

// vraag 6 (Object Georiënteerde Project - Aanvullend): separate header files
// Elke klasse in dit project heeft zijn eigen .h/.cpp-paar: Device,
// Light, Thermostat, DoorLock, Camera en Room. Niets staat samen in
// één groot bestand -- dit houdt elke klasse overzichtelijk en
// onafhankelijk aanpasbaar zonder de rest van het project te moeten
// doorzoeken.

// vraag 8: useful and correct object composition
// Objectcompositie is hier nuttig en correct toegepast omdat Room
// "has-a" verzameling Devices (via unique_ptr), niet via overerving
// -- een Room ís geen Device. De devices worden als bouwstenen
// gecombineerd om de functionaliteit van een kamer (toestellen
// groeperen, opzoeken, tonen) te realiseren.
class Room
{
public:
    Room(std::string name);

    void addDevice(std::unique_ptr<Device> device);
    Device* findDevice(const std::string& name) const;
    void printAllDevices() const;

private:
    std::string name_;
    std::vector<std::unique_ptr<Device>> devices_;
};
