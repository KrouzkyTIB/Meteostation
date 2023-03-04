//
// Created by jiri on 4.3.23.
//

#include "WifiHandler.hpp"
#include "filesystem/Filesystem.hpp"
#include "ESP8266WiFi.h"
#include "PinDefinitions.hpp"


#define WIFI_CONFIG_FILE "wifi_config"
#define SOFT_AP_SSID "TIB_meteo"

const IPAddress WifiHandler::subnet(10, 0, 0, 0);
const IPAddress WifiHandler::gateway(10, 0, 0, 255);
const IPAddress WifiHandler::ipAddress(10, 0, 0, 10);

void WifiHandler::init() {

    if (filesystem::doesFileExists(WIFI_CONFIG_FILE)) {
        std::vector<std::string> configLines = filesystem::readAllLinesFromFile(WIFI_CONFIG_FILE);
        this->ssid = configLines.at(0);
        this->password = configLines.at(1);
        WiFi.begin(this->ssid.c_str(), this->password.c_str());
        WiFi.mode(WiFiMode_t::WIFI_STA);
        while (WiFi.status() != WL_CONNECTED) {
            digitalWrite(WIFI_CONNECTED_PIN, HIGH);
            delay(50);
            digitalWrite(WIFI_CONNECTED_PIN, LOW);
            delay(50);
        }
        digitalWrite(WIFI_CONNECTED_PIN, HIGH);
        delay(1000);
        digitalWrite(WIFI_CONNECTED_PIN, LOW);
        return;
    }

    WiFi.mode(WiFiMode_t::WIFI_AP);
    WiFi.softAPConfig(ipAddress, gateway, subnet);
    WiFi.softAP(SOFT_AP_SSID);
    Serial.println(WiFi.localIP());
}
