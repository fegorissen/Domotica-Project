#include <iostream>
#include <cassert>
#include <memory>
#include "Device.h"
#include "Light.h"
#include "Thermostat.h"
#include "Doorlock.h"
#include "Camera.h"
#include "Room.h"
#include "LogHistory.h"
#include "DeviceFactory.h"
#include "DeviceNotFoundException.h"
#include <sstream>

// vraag 44 (Object Georiënteerde Project - Aanvullend): test-driven
// development
// Klein, zelfgemaakt testprogramma (los van main.cpp, apart te
// bouwen) dat de belangrijkste functionaliteit van het project
// verifieert via assert()-checks. Elke test print duidelijk wat er
// gecontroleerd wordt, zodat een gefaalde assert() makkelijk terug
// te herleiden is naar de test die faalde.

using namespace smarthome;

void testDeviceDefaultsToOff()
{
    Light lamp("Testlamp");
    assert(lamp.isOn() == false);
    std::cout << "OK: nieuw device staat standaard uit" << std::endl;
}

void testToggleFlipsState()
{
    Light lamp("Testlamp");
    lamp.toggle();
    assert(lamp.isOn() == true);
    lamp.toggle();
    assert(lamp.isOn() == false);
    std::cout << "OK: toggle() wisselt de status correct om" << std::endl;
}

void testSetNameRejectsEmpty()
{
    Light lamp("Testlamp");
    lamp.setName("");
    assert(lamp.getName() == "Testlamp"); // ongewijzigd, want lege naam geweigerd
    lamp.setName("Nieuwe naam");
    assert(lamp.getName() == "Nieuwe naam");
    std::cout << "OK: setName() weigert een lege naam" << std::endl;
}

void testThermostatClampsTemperature()
{
    Thermostat thermostaat("Verwarming", 999.0); // buiten bereik bij aanmaak
    assert(thermostaat.getTargetTemperature() == 30.0);
    thermostaat.setTargetTemperature(-50.0);
    assert(thermostaat.getTargetTemperature() == 10.0);
    std::cout << "OK: Thermostat begrenst temperatuur via clamp<T>()" << std::endl;
}

void testDoorLockStatusText()
{
    DoorLock deur("Voordeur");
    assert(deur.status() == "ontgrendeld");
    deur.toggle();
    assert(deur.status() == "vergrendeld");
    std::cout << "OK: DoorLock toont correcte status-tekst" << std::endl;
}

void testFindDeviceReturnsNullptrWhenMissing()
{
    Room room("Testkamer");
    room.addDevice(std::make_unique<Light>("Lamp1"));
    assert(room.findDevice("Lamp1") != nullptr);
    assert(room.findDevice("NietBestaand") == nullptr);
    std::cout << "OK: findDevice() geeft nullptr terug voor onbestaand device" << std::endl;
}

void testCopyConstructorMakesDeepCopy()
{
    Room room("Testkamer");
    room.addDevice(std::make_unique<Light>("Lamp1"));

    Room kopie = room;
    Device* lampInKopie = kopie.findDevice("Lamp1");
    assert(lampInKopie != nullptr);
    lampInKopie->toggle();

    Device* lampInOrigineel = room.findDevice("Lamp1");
    assert(lampInOrigineel->isOn() == false); // origineel bleef ongewijzigd
    assert(lampInKopie->isOn() == true);
    std::cout << "OK: copy constructor maakt een echte deep copy (geen gedeelde state)" << std::endl;
}

void testDeviceFactoryReturnsNullptrForUnknownType()
{
    auto device = createDeviceFromType("OnbekendType", "Test");
    assert(device == nullptr);

    auto lightDevice = createDeviceFromType("Light", "TestLamp");
    assert(lightDevice != nullptr);
    assert(lightDevice->getTypeName() == "Light");
    std::cout << "OK: DeviceFactory geeft nullptr terug voor onbekend type, en correct type anders" << std::endl;
}

void testGetDeviceOrThrowThrowsCorrectly()
{
    Room room("Testkamer");
    room.addDevice(std::make_unique<Light>("Lamp1"));

    bool exceptionGegooid = false;
    try
    {
        room.getDeviceOrThrow("NietBestaand");
    }
    catch (const DeviceNotFoundException&)
    {
        exceptionGegooid = true;
    }
    assert(exceptionGegooid == true);
    std::cout << "OK: getDeviceOrThrow() gooit DeviceNotFoundException correct" << std::endl;
}

void testLogHistoryStoresMessages()
{
    LogHistory log(3);
    log.add("bericht 1");
    log.add("bericht 2");

    std::ostringstream oss;
    log.printAll(oss);
    std::string output = oss.str();
    assert(output.find("bericht 1") != std::string::npos);
    assert(output.find("bericht 2") != std::string::npos);
    std::cout << "OK: LogHistory (new[]/delete[]) slaat berichten correct op" << std::endl;
}

int main()
{
    std::cout << "=== Smarthome unit tests ===" << std::endl;

    testDeviceDefaultsToOff();
    testToggleFlipsState();
    testSetNameRejectsEmpty();
    testThermostatClampsTemperature();
    testDoorLockStatusText();
    testFindDeviceReturnsNullptrWhenMissing();
    testCopyConstructorMakesDeepCopy();
    testDeviceFactoryReturnsNullptrForUnknownType();
    testGetDeviceOrThrowThrowsCorrectly();
    testLogHistoryStoresMessages();

    std::cout << "=== Alle testen geslaagd! ===" << std::endl;
    return 0;
}
