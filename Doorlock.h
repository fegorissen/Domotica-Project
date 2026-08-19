#pragma once
#include "Device.h"

// vraag 11: useful and correct virtual function
// toggle() en status() zijn hier gemarkeerd met "override" in plaats
// van "virtual" te herhalen. Dat is de correcte, moderne manier: de
// compiler controleert dan of deze functies écht een virtuele functie
// van Device overschrijven (bv. een typfout in de signatuur geeft nu
// een duidelijke compile-fout, in plaats van stilzwijgend een nieuwe,
// ongebruikte functie aan te maken die nooit polymorf aangeroepen
// wordt).
class DoorLock : public Device
{
public:
    DoorLock(std::string name);

    void toggle() override;
    std::string status() const override;
};
