#pragma once
#include <QObject>
#include "Device.h"

namespace smarthome
{
// vraag 43 (Object Georiënteerde Project - Aanvullend): useful
// usage of signals/slots
// Camera erft van QObject om Qt's signal/slot-mechanisme te
// kunnen gebruiken. Dit ontkoppelt Camera van wie er precies
// luistert naar beweging-events.
class Camera : public QObject, public Device
{
    Q_OBJECT

public:
    explicit Camera(std::string name);

    void toggle() override;
    std::string status() const override;
    std::string getTypeName() const override;
    std::unique_ptr<Device> clone() const override;

    void triggerMotion();

    // vraag 51 (Object Georiënteerde Project - Aanvullend): nice extra (RuleEngine)
    // Publieke getter, nodig zodat RuleEngine-condities (lambda's)
    // de motion-status kunnen checken zonder een friend of interne
    // toegang te vereisen.
    bool isMotionDetected() const;

signals:
    void motionDetectedSignal(const std::string& deviceName);

private:
    // vraag 5: useful and correct encapsulation
    // vraag 31 (Object Georiënteerde Project - Aanvullend): at least 4 useful bool (2/4)
    bool motionDetected_ = false;
};
}
