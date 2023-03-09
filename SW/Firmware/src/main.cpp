#include <Arduino.h>
#include "sensor/Sensor.hpp"
#include "PinDefinitions.hpp"
#include "display/Display.hpp"
#include "filesystem/Filesystem.hpp"
#include "wifi/WifiHandler.hpp"
#include "server/ServerWrapper.hpp"

#define DEBOUNCING_TIME 100

uint64_t buttonClickedTimestamp = 0;


Sensor indoorSensor(INDOOR_SENSOR_PIN);
Sensor outdoorSensor(OUTDOOR_SENSOR_PIN);
Display display(indoorSensor, outdoorSensor);
WifiHandler wifiHandler(display);

void resetWifiButtonHandler();

void setup() {
    pinMode(WIFI_CONNECTED_PIN, OUTPUT);
    pinMode(RESET_WIFI_SETTINGS_PIN, INPUT_PULLUP);
    Serial.begin(115200);
    filesystem::init();
    indoorSensor.init();
    outdoorSensor.init();
    display.init();
    display.turnBacklightOn();
    wifiHandler.init();
    ServerWrapper::init(&wifiHandler, &indoorSensor, &outdoorSensor, &display);
    attachInterrupt(digitalPinToInterrupt(RESET_WIFI_SETTINGS_PIN), resetWifiButtonHandler, FALLING);
}

void loop() {
    display.update();
    ServerWrapper::handleClient();
    if (buttonClickedTimestamp + DEBOUNCING_TIME < millis() || buttonClickedTimestamp > millis()) {
        buttonClickedTimestamp = 0;
    }
}

void ICACHE_RAM_ATTR resetWifiButtonHandler() {
    if (buttonClickedTimestamp == 0) {
        wifiHandler.resetSettings();
        buttonClickedTimestamp = millis();
    }
}





