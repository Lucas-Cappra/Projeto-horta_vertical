#ifndef SOIL_MOISTURE_SENSOR_H
#define SOIL_MOISTURE_SENSOR_H

#include <Arduino.h>

class SoilMoistureSensor {
public:
    SoilMoistureSensor(uint8_t pin);
    int readMoisture();
    int calculateAverageMoisture(int samples);

private:
    uint8_t pin;
};

#endif
