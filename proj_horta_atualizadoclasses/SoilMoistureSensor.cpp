#include "SoilMoistureSensor.h"

SoilMoistureSensor::SoilMoistureSensor(uint8_t pin) : pin(pin) {
    pinMode(pin, INPUT);
}

int SoilMoistureSensor::readMoisture() {
    return analogRead(pin);
}

int SoilMoistureSensor::calculateAverageMoisture(int samples) {
    long sum = 0;
    for (int i = 0; i < samples; ++i) {
        sum += readMoisture();
        delay(100);
    }
    return sum / samples;
}
