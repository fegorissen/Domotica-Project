#include "Device.h"

// vraag 3 (Object Georiënteerde Project - Aanvullend): no globals, but statics if needed
// De definitie/initialisatie van de static member. Dit is de ENIGE
// plek in het hele programma waar deze teller bestaat -- gedeeld door
// alle Device-objecten, in plaats van elk object zijn eigen kopie te
// geven (wat bij een gewone member variable wel zou gebeuren).
unsigned char Device::nextId_ = 1;

Device::Device(std::string name)
    : name_(name), id_(nextId_++)
{
}

std::string Device::getName() const
{
    return name_;
}

bool Device::isOn() const
{
    return on_;
}

unsigned char Device::getId() const
{
    return id_;
}
