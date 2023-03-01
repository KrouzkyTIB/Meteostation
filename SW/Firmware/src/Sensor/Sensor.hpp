//
// Created by jiri on 1.3.23.
//

#ifndef FIRMWARE_SENSOR_HPP
#define FIRMWARE_SENSOR_HPP


#include <Arduino.h>
#include <DHT.h>

class Sensor {
private:
    uint64_t lastMeasurementMillis;
    float temperature;
    float humidity;
    void updateMeasurements();
    DHT dht;

public:
    explicit Sensor(uint8_t pinNumber);
    float getTemperature();
    float getHumidity();
    void init();

};


#endif //FIRMWARE_SENSOR_HPP
