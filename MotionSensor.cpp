#include "MotionSensor.h"
#include <chrono>

namespace smarthome
{
    MotionSensor::MotionSensor(Camera& camera)
        : camera_(camera)
    {
    }

    // vraag 41 (Object Georiënteerde Project - Aanvullend): useful
    // usage of threads
    // Destructor: stopt de thread ALTIJD vóór het object vernietigd
    // wordt. Dit voorkomt de klassieke thread-crash: een std::thread
    // die nog "joinable" is bij zijn eigen destructie laat het hele
    // programma crashen via std::terminate().
    MotionSensor::~MotionSensor()
    {
        stop();
    }

    void MotionSensor::start()
    {
        if (running_)
        {
            return;
        }
        running_ = true;
        worker_ = std::thread(&MotionSensor::run, this);
    }

    void MotionSensor::stop()
    {
        running_ = false;
        if (worker_.joinable())
        {
            worker_.join();
        }
    }

    void MotionSensor::run()
    {
        int iteration = 0;
        while (running_ && iteration < 3)
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(200));
            if (camera_.isOn())
            {
                camera_.triggerMotion();
            }
            ++iteration;
        }
    }
}
