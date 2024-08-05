#ifndef SENSOR_DHT_H
#define SENSOR_DHT_H

#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>

class SensorDHT {
public:
    SensorDHT(uint8_t pin, uint8_t type);
    void begin();
    float readTemperature();
    float readHumidity();

private:
    DHT_Unified dht;
};

#endif
