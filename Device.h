#pragma once
#include <string>
#include <memory>

// vraag 24 (Object Georiënteerde Project - Aanvullend): correct usage of inline function
// Klein, veelgebruikt hulpfunctietje dat in de header staat. Elke .cpp
// die Device.h include (Light.cpp, Thermostat.cpp, Doorlock.cpp,
// Camera.cpp, Room.cpp) krijgt zijn eigen kopie van deze functie op
// compile-tijd. Zonder "inline" zou dit een linker-fout geven
// ("multiple definition of onOffText") zodra meer dan één .cpp-bestand
// deze header include -- wat hier letterlijk het geval is.
inline std::string onOffText(bool on)
{
    return on ? "aan" : "uit";
}

// vraag 4: useful and correct abstraction
// vraag 9: useful and correct base class
// vraag 10: useful and correct abstract base class
// Device legt de gemeenschappelijke interface vast (naam, aan/uit,
// toggle, status) voor elk toestel, zonder de details van een
// specifiek toestel te tonen. Doordat toggle()/status() pure virtual
// zijn (= 0), kan Device nooit rechtstreeks geïnstantieerd worden.
class Device
{
public:
    // vraag 13 (Object Georiënteerde Project - Aanvullend): at least 2 parameterized constructors
    // Vereist een naam bij aanmaak -- gebruikt door alle afgeleide
    // klassen (Light, Thermostat, DoorLock, Camera) in hun eigen
    // constructor via Device(name).
    Device(std::string name);

    // vraag 11: useful and correct virtual function
    // Virtueel, want objecten worden later via een Device-pointer
    // gebruikt (zie main.cpp) en moeten correct opgeruimd worden.
    virtual ~Device() = default;

    virtual void toggle() = 0;
    virtual std::string status() const = 0;

    // vraag 14 (Object Georiënteerde Project - Aanvullend): at least 2 copy constructors
    // clone() is nodig omdat Room een DIEPE kopie van al zijn devices
    // moet kunnen maken (zie Room.cpp): een unique_ptr<Device> kan niet
    // rechtstreeks gekopieerd worden, dus elk concreet type (Light,
    // Thermostat, ...) implementeert clone() door zijn EIGEN copy
    // constructor aan te roepen via make_unique<Type>(*this).
    virtual std::unique_ptr<Device> clone() const = 0;

    // vraag 23 (Object Georiënteerde Project - Aanvullend): useful getters and setters for member variables
    // Getter: geeft de huidige naam terug, zonder dat de aanroeper
    // rechtstreeks toegang krijgt tot het private/protected veld.
    std::string getName() const;

    // vraag 23 (Object Georiënteerde Project - Aanvullend): useful getters and setters for member variables
    // Setter met validatie: weigert een lege naam, in plaats van
    // zomaar elke waarde toe te laten.
    void setName(const std::string& name);

    bool isOn() const;

    // vraag 20 (Object Georiënteerde Project - Aanvullend): useful member function
    // Geeft het unieke ID van dit device terug, toegekend bij aanmaak.
    unsigned char getId() const;

    // vraag 4 (Object Georiënteerde Project - Aanvullend): correct protections
    // protected: name_/on_ zijn nodig in de afgeleide klassen (Light/
    // Thermostat/DoorLock/Camera gebruiken ze rechtstreeks in hun eigen
    // toggle()), maar mogen niet van buiten de klasse-hiërarchie
    // aangepast worden.
protected:
    std::string name_;
    bool on_ = false;

    // private: nextId_ en id_ zijn interne implementatiedetails die zelfs
    // afgeleide klassen niet nodig hebben -- enkel Device zelf beheert de
    // ID-toekenning.
private:
    // vraag 3 (Object Georiënteerde Project - Aanvullend): no globals, but statics if needed
    // nextId_ is een static member: gedeeld door alle Device-objecten
    // (er bestaat maar één "teller" voor de hele klasse), maar netjes
    // ingekapseld binnen Device zelf -- geen globale variabele die
    // van overal in het programma rechtstreeks aanpasbaar zou zijn.
    static unsigned char nextId_;
    unsigned char id_;
};
