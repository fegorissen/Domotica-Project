#pragma once
#include <string>
#include <memory>
#include <ostream>

// vraag 27 (Object Georiënteerde Project - Aanvullend): everything in
// one or more self-made namespace(s)
// Alle klassen en functies van dit project zitten in de zelfgemaakte
// namespace "smarthome", zodat ze nooit botsen met gelijknamige
// klassen/functies uit externe libraries.
namespace smarthome
{
// vraag 24 (Object Georiënteerde Project - Aanvullend): correct usage of inline function
// Klein, veelgebruikt hulpfunctietje dat in de header staat. Elke
// .cpp die Device.h include krijgt zijn eigen kopie van deze
// functie op compile-tijd. Zonder "inline" zou dit een linker-
// fout geven ("multiple definition") zodra meer dan één .cpp-
// bestand deze header include.
inline std::string onOffText(bool on)
{
    return on ? "aan" : "uit";
}

// vraag 4: useful and correct abstraction
// vraag 9: useful and correct base class
// vraag 10: useful and correct abstract base class
// Device legt de gemeenschappelijke interface vast (naam, aan/uit,
// toggle, status) voor elk toestel, zonder de details van een
// specifiek toestel te tonen. Doordat toggle()/status() pure
// virtual zijn (= 0), kan Device nooit rechtstreeks
// geïnstantieerd worden.
class Device
{
public:
    // vraag 13 (Object Georiënteerde Project - Aanvullend): at least 2 parameterized constructors
    Device(std::string name);

    // vraag 11: useful and correct virtual function
    virtual ~Device() = default;

    virtual void toggle() = 0;
    virtual std::string status() const = 0;

    // vraag 14 (Object Georiënteerde Project - Aanvullend): at least 2 copy constructors
    virtual std::unique_ptr<Device> clone() const = 0;

    // vraag 23 (Object Georiënteerde Project - Aanvullend): useful getters and setters for member variables
    std::string getName() const;
    void setName(const std::string& name);

    bool isOn() const;

    // vraag 20 (Object Georiënteerde Project - Aanvullend): useful member function
    unsigned char getId() const;

    // vraag 26 (Object Georiënteerde Project - Aanvullend): useful friend function or class
    // operator<< heeft toegang nodig tot het PRIVATE id_-veld, dat
    // bewust geen eigen publieke getter heeft buiten dit debug-
    // printformaat. Zonder friend zou dit ofwel een publieke
    // "debug getter" vereisen (wat encapsulatie verzwakt), ofwel
    // onmogelijk zijn.
    friend std::ostream& operator<<(std::ostream& os, const Device& device);

    // vraag 4 (Object Georiënteerde Project - Aanvullend): correct protections
protected:
    std::string name_;
    bool on_ = false;

private:
    // vraag 3 (Object Georiënteerde Project - Aanvullend): no globals, but statics if needed
    static unsigned char nextId_;
    unsigned char id_;
};
}
