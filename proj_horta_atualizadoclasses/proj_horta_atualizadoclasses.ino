#include <Arduino.h>
#include "SensorDHT.h"
#include "DisplayOLED.h"
#include "SoilMoistureSensor.h"

#define DHTPIN 2
#define DHTTYPE DHT22
#define SCREEN_I2C_ADDR 0x3C
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define PINO_SENSOR A0

SensorDHT sensorDHT(DHTPIN, DHTTYPE);
DisplayOLED displayOLED(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_I2C_ADDR);
SoilMoistureSensor soilMoistureSensor(PINO_SENSOR);

void setup() {
    Serial.begin(9600);
    sensorDHT.begin();
    displayOLED.begin();
}

void loop() {
    displayOLED.clear();

    float temperature = sensorDHT.readTemperature();
    float humidity = sensorDHT.readHumidity();

    if (isnan(temperature)) {
        displayOLED.printMessage("Erro na leitura da Temp!", 0, 20);
    } else {
        displayOLED.printMessage("Temperatura: " + String(temperature) + " C", 0, 20);
    }

    if (isnan(humidity)) {
        displayOLED.printMessage("Erro na leitura da Umidade!", 0, 30);
    } else {
        displayOLED.printMessage("Umidade: " + String(humidity) + " %", 0, 30);
    }

    int averageMoisture = soilMoistureSensor.calculateAverageMoisture(5);
    displayOLED.printMessage("Media Umidade: " + String(averageMoisture), 0, 50);

    if (averageMoisture >= 500) {
        displayOLED.printMessage("Esta seco", 10, 60);
    } else {
        displayOLED.printMessage("Esta umido", 10, 60);
    }

    delay(10000);
}
