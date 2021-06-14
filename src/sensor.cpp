#ifndef SENSOR
#define SENSOR

#include "Arduino.h"
struct Sensor
{
    double theta, phi; // polar direction

    void InitPin(int XPin, int YPin)
    {
    }

    double get_theta()
    {
        return theta;
    }

    double get_phi()
    {
        return phi;
    }
};

#endif
