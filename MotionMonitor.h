#pragma once
#include <QObject>
#include <string>
#include <iostream>

namespace smarthome
{
// vraag 43 (Object Georiënteerde Project - Aanvullend): useful
// usage of signals/slots
// Luistert naar Camera's motionDetectedSignal via een slot. Camera
// weet niets over deze klasse -- de koppeling gebeurt volledig via
// Qt's connect()-mechanisme in main.cpp.
class MotionMonitor : public QObject
{
    Q_OBJECT

public slots:
    void onMotionDetected(const std::string& deviceName)
    {
        std::cout << "[MotionMonitor] Beweging gemeld door: " << deviceName << std::endl;
    }
};
}
