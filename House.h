#pragma once
#include <string>
#include <map>
#include <memory>
#include "Room.h"

namespace smarthome
{
// vraag 51 (Object Georiënteerde Project - Aanvullend): nice extra
// House is een NIEUW niveau van object compositie (vergelijk met
// vraag 8: Room "has-a" Devices): House "has-a" verzameling Rooms,
// elk geïdentificeerd op naam. Dit breidt de architectuur van het
// project echt uit -- een huis met meerdere kamers, in plaats van
// een los te maken tool erbovenop.
class House
{
public:
    explicit House(std::string name);

    // Voegt een nieuwe, lege kamer toe en geeft er een referentie
    // naar terug, zodat de aanroeper er meteen devices aan kan
    // toevoegen.
    Room& addRoom(const std::string& roomName);

    // Geeft nullptr terug als de kamer niet bestaat (vraag 37:
    // useful usage of nullptr, consistent met Room::findDevice()).
    Room* findRoom(const std::string& roomName);
    const Room* findRoom(const std::string& roomName) const;

    std::map<std::string, Room>& rooms();
    const std::map<std::string, Room>& rooms() const;

    // Telt het totaal aantal devices over ALLE kamers heen.
    int totalDeviceCount() const;

    void saveToFile(const std::string& path) const;
    void loadFromFile(const std::string& path);

    const std::string& getName() const;

private:
    std::string name_;
    // std::map i.p.v. vector: kamers worden op naam opgezocht,
    // niet op positie -- een tweede, andere toepassing van
    // useful container class (vraag 36) dan Room's eigen
    // countDevicesByType().
    std::map<std::string, Room> rooms_;
};
}
