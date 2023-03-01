#include <Arduino.h>
#include "Sensor/Sensor.hpp"
#include "PinDefinitions.hpp"

Sensor indoorSensor(INDOOR_SENSOR_PIN);

void setup() {
    indoorSensor.init();
    Serial.begin(115200);
}

void loop() {
    Serial.printf("Temp: %f, Humi: %f\n", indoorSensor.getTemperature(), indoorSensor.getHumidity());
    delay(500);
}