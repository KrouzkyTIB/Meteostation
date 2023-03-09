//
// Created by jiri on 1.3.23.
//

#include "Sensor.hpp"

#define UPDATE_PERIOD_MS 2000


Sensor::Sensor(const uint8_t pinNumber) : dht(pinNumber, DHT22) {
    this->humidity = 0;
    this->lastMeasurementMillis = 0;
    this->temperature = 0;
}

void Sensor::updateMeasurements() {
    if (this->lastMeasurementMillis + UPDATE_PERIOD_MS <= millis() || millis() < this->lastMeasurementMillis) {
        this->lastMeasurementMillis = millis();
        this->temperature = dht.readTemperature();
        this->humidity = dht.readHumidity();
    }
}

float Sensor::getTemperature() {
    updateMeasurements();
    return this->temperature;
}

float Sensor::getHumidity() {
    updateMeasurements();
    return this->humidity;
}

void Sensor::init() {
    dht.begin();
}

float Sensor::getValueIfCorrect(float value) {
    return 0;
}



