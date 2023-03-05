//
// Created by jiri on 4.3.23.
//

#include "WifiHandler.hpp"
#include "filesystem/Filesystem.hpp"
#include "ESP8266WiFi.h"
#include "PinDefinitions.hpp"


#define WIFI_CONFIG_FILE "wifi_config"
#define SOFT_AP_SSID "TIB_meteo"


const IPAddress WifiHandler::ipAddress(192, 168, 0, 10);
const IPAddress WifiHandler::gateway(192, 168, 0, 9);
const IPAddress WifiHandler::subnet(255, 255, 255, 0);

void WifiHandler::init() {

    if (filesystem::doesFileExists(WIFI_CONFIG_FILE)) {
        std::vector<std::string> configLines = filesystem::readAllLinesFromFile(WIFI_CONFIG_FILE);
        for(auto l : configLines){
            Serial.println(l.c_str());
        }
        this->ssid = configLines.at(0);
        this->password = configLines.at(1);
        Serial.printf("ssid: %s password: %s |\n", this->ssid.c_str(), this->password.c_str());
        WiFi.begin(this->ssid.c_str(), this->password.c_str());
        WiFi.mode(WiFiMode_t::WIFI_STA);
        waitUntilConnectedToWifi();
        return;
    }

    WiFi.mode(WiFiMode_t::WIFI_AP);
    WiFi.softAPConfig(ipAddress, gateway, subnet);
    WiFi.softAP(SOFT_AP_SSID);
    Serial.println(WiFi.softAPIP());
}

WifiHandler::WifiHandler() : connectedToWifi(false) {

}

bool WifiHandler::isConnectedToWifi() const {
    return this->connectedToWifi;
}

void WifiHandler::setNewConfig(const std::string &newSsid, const std::string &newPassword) {
    this->ssid = newSsid;
    this->password = newPassword;
    WiFi.softAPdisconnect(true);
    WiFi.mode(WiFiMode_t::WIFI_STA);
    WiFi.begin(this->ssid.c_str(), this->password.c_str());
    waitUntilConnectedToWifi();
    this->connectedToWifi = true;
    std::vector<std::string> config;
    config.push_back(this->ssid);
    config.push_back(this->password);
    filesystem::saveLinesToFile(WIFI_CONFIG_FILE, config);
}

void WifiHandler::waitUntilConnectedToWifi() {
    while (WiFi.status() != WL_CONNECTED) {
        digitalWrite(WIFI_CONNECTED_PIN, HIGH);
        delay(50);
        digitalWrite(WIFI_CONNECTED_PIN, LOW);
        delay(50);
    }
    digitalWrite(WIFI_CONNECTED_PIN, HIGH);
    delay(1000);
    digitalWrite(WIFI_CONNECTED_PIN, LOW);
    this->connectedToWifi = true;
}
