#pragma once
#include <thread>
#include <atomic>
#include "Camera.h"

namespace smarthome
{
// vraag 41 (Object Georiënteerde Project - Aanvullend): useful
// usage of threads
// Simuleert een achtergrond-sensor die periodiek een camera checkt
// op beweging, terwijl de hoofdthread ondertussen gewoon doorgaat.
// De thread wordt in de destructor altijd netjes gestopt en
// gejoined -- zonder dat zou het programma crashen (std::terminate)
// als de thread nog loopt bij het afsluiten.
class MotionSensor
{
public:
    explicit MotionSensor(Camera& camera);
    ~MotionSensor();

    MotionSensor(const MotionSensor&) = delete;
    MotionSensor& operator=(const MotionSensor&) = delete;

    void start();
    void stop();

private:
    void run();

    Camera& camera_;
    std::thread worker_;
    std::atomic<bool> running_{false};
};
}
