#include <Arduino.h>
#include "sensor/Sensor.hpp"
#include "PinDefinitions.hpp"
#include "display/Display.hpp"

Sensor indoorSensor(INDOOR_SENSOR_PIN);
//Sensor outdoorSensor(OUTDOOR_SENSOR_PIN);
Display display(indoorSensor, indoorSensor);

void setup() {
    indoorSensor.init();
//    outdoorSensor.init();
    display.init();
    Serial.begin(115200);
    display.turnBacklightOn();
}

void loop() {
    display.update();
}