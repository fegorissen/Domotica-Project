#pragma once
#include "Device.h"

class Light : public Device
{
public:
    Light(std::string name);

    void toggle() override;
    std::string status() const override;

private:
    bool brightness_ = 80;
};
