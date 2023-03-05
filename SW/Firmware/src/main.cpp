#include <Arduino.h>
#include "sensor/Sensor.hpp"
#include "PinDefinitions.hpp"
#include "display/Display.hpp"
#include "filesystem/Filesystem.hpp"
#include "wifi/WifiHandler.hpp"
#include "server/ServerWrapper.hpp"

Sensor indoorSensor(INDOOR_SENSOR_PIN);
Sensor outdoorSensor(OUTDOOR_SENSOR_PIN);
Display display(indoorSensor, outdoorSensor);
WifiHandler wifiHandler(display);


void setup() {
    pinMode(WIFI_CONNECTED_PIN, OUTPUT);
    Serial.begin(115200);
    filesystem::init();
    indoorSensor.init();
    outdoorSensor.init();
    display.init();
    display.turnBacklightOn();
    wifiHandler.init();
    ServerWrapper::init(&wifiHandler, &indoorSensor, &outdoorSensor);
}

void loop() {
    display.update();
    ServerWrapper::handleClient();
}





