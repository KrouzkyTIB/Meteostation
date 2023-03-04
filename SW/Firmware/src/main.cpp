#include <Arduino.h>
#include "sensor/Sensor.hpp"
#include "PinDefinitions.hpp"
#include "display/Display.hpp"
#include "filesystem/Filesystem.hpp"
#include "wifi/WifiHandler.hpp"

Sensor indoorSensor(INDOOR_SENSOR_PIN);
Sensor outdoorSensor(OUTDOOR_SENSOR_PIN);
Display display(indoorSensor, outdoorSensor);
WifiHandler wifiHandler;


void setup() {
    Serial.begin(115200);
    filesystem::init();
    indoorSensor.init();
    outdoorSensor.init();
    wifiHandler.init();
    display.init();
    display.turnBacklightOn();
}

void loop() {
    display.update();
}