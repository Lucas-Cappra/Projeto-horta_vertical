#include "SensorDHT.h"

SensorDHT::SensorDHT(uint8_t pin, uint8_t type) : dht(pin, type) {}

void SensorDHT::begin() {
    dht.begin();
}

float SensorDHT::readTemperature() {
    sensors_event_t event;
    dht.temperature().getEvent(&event);
    if (!isnan(event.temperature)) {
        return event.temperature;
    } else {
        return NAN;
    }
}

float SensorDHT::readHumidity() {
    sensors_event_t event;
    dht.humidity().getEvent(&event);
    if (!isnan(event.relative_humidity)) {
        return event.relative_humidity;
    } else {
        return NAN;
    }
}
