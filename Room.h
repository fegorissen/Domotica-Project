#pragma once
#include <string>
#include <vector>
#include <memory>
#include "Device.h"

// vraag 6 (Object Georiënteerde Project - Aanvullend): separate header files
// Elke klasse in dit project heeft zijn eigen .h/.cpp-paar: Device,
// Light, Thermostat, DoorLock, Camera en Room -- niets staat samen in
// één groot bestand.

// vraag 8: useful and correct object composition
// Room "has-a" verzameling Devices (via unique_ptr), geen inheritance.
class Room
{
public:
    // vraag 13 (Object Georiënteerde Project - Aanvullend): at least 2 parameterized constructors
    // Vereist een naam bij aanmaak, bv. Room livingRoom("Woonkamer").
    Room(std::string name);

    // vraag 12 (Object Georiënteerde Project - Aanvullend): at least 2 default constructors
    // vraag 17 (Object Georiënteerde Project - Aanvullend): constructor forwarding
    // Room() hergebruikt de parameterized constructor met een
    // standaardnaam, i.p.v. zelf opnieuw name_ te initialiseren.
    Room();

    void addDevice(std::unique_ptr<Device> device);
    Device* findDevice(const std::string& name) const;
    void printAllDevices() const;

private:
    std::string name_;
    // vraag 8: useful and correct object composition
    // Dit is de eigenlijke compositie: Room bezit een verzameling
    // Device's als lid-variabele, gecombineerd als bouwsteen om de
    // functionaliteit van een kamer te realiseren.
    std::vector<std::unique_ptr<Device>> devices_;
};
