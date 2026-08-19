#pragma once
#include <string>
#include <vector>
#include <memory>
#include "Device.h"

class Room
{
public:
    Room(std::string name);

    void addDevice(std::unique_ptr<Device> device);
    Device* findDevice(const std::string& name) const;
    void printAllDevices() const;

private:
    std::string name_;
    std::vector<std::unique_ptr<Device>> devices_;
};
