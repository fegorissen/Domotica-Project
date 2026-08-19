#pragma once
#include <string>

class Device
{
public:
    Device(std::string name);
    virtual ~Device() = default;

    virtual void toggle() = 0;
    virtual std::string status() const = 0;

    std::string getName() const;
    bool isOn() const;

protected:
    std::string name_;
    bool on_ = false;
};
