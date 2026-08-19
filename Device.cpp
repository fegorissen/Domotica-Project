#include "Device.h"

// vraag 3 (Object Georiënteerde Project - Aanvullend): no globals, but statics if needed
// De definitie/initialisatie van de static member. Dit is de ENIGE
// plek in het hele programma waar deze teller bestaat -- gedeeld door
// alle Device-objecten, in plaats van elk object zijn eigen kopie te
// geven (wat bij een gewone member variable wel zou gebeuren).
unsigned char Device::nextId_ = 1;

// vraag 16 (Object Georiënteerde Project - Aanvullend): member initialization in constructors
// Het stuk na de ":" is de member-initialisatielijst -- name_ en id_
// worden hier DIRECT met hun juiste waarde aangemaakt, in plaats van
// eerst met een default-waarde aangemaakt te worden en pas daarna in
// het { }-blok overschreven te worden.
Device::Device(std::string name)
    : name_(name), id_(nextId_++)
{
}

std::string Device::getName() const
{
    return name_;
}

// vraag 23 (Object Georiënteerde Project - Aanvullend): useful getters and setters for member variables
// Weigert een lege naam -- de kern van waarom dit een NUTTIGE setter
// is: er zit echte logica in, niet enkel een blinde toewijzing.
void Device::setName(const std::string& name)
{
    if (!name.empty())
    {
        name_ = name;
    }
}

bool Device::isOn() const
{
    return on_;
}

unsigned char Device::getId() const
{
    return id_;
}
