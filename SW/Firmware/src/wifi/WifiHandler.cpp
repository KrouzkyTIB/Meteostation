//
// Created by jiri on 4.3.23.
//

#include "WifiHandler.hpp"
#include "filesystem/Filesystem.hpp"
#include "ESP8266WiFi.h"
#include "PinDefinitions.hpp"


#define WIFI_CONFIG_FILE "wifi_config"
#define SOFT_AP_SSID "TIB_meteo"
#define RESETTING_WIFI_LABEL_UPPER "Resetting"
#define RESETTING_WIFI_LABEL_LOWER "settings"
#define DEFAULT_WIFI_LABEL "TIB meteo"
#define CONNECTED_LABEL "Connected!"
#define CONNECTING_LABEL_UPPER "Connecting to"
#define CONNECTING_LABEL_LOWER "local WiFi"


const IPAddress WifiHandler::ipAddress(192, 168, 0, 10);
const IPAddress WifiHandler::gateway(192, 168, 0, 9);
const IPAddress WifiHandler::subnet(255, 255, 255, 0);

void WifiHandler::init() {

    if (filesystem::doesFileExists(WIFI_CONFIG_FILE)) {
        std::vector<std::string> configLines = filesystem::readAllLinesFromFile(WIFI_CONFIG_FILE);
        this->ssid = configLines.at(0);
        this->password = configLines.at(1);
        WiFi.begin(this->ssid.c_str(), this->password.c_str());
        WiFi.mode(WiFiMode_t::WIFI_STA);
        waitUntilConnectedToWifi();
        showWifiSettings();
        return;
    }

    WiFi.mode(WiFiMode_t::WIFI_AP);
    WiFi.softAPConfig(ipAddress, gateway, subnet);
    WiFi.softAP(SOFT_AP_SSID);
    showWifiSettings();
}

WifiHandler::WifiHandler(Display &display) : connectedToWifi(false), display(display) {

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
    showWifiSettings();
}

void WifiHandler::waitUntilConnectedToWifi() {
    display.showMessage(CONNECTING_LABEL_UPPER, CONNECTING_LABEL_LOWER);
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

std::string WifiHandler::getIp() const {
    if (isConnectedToWifi()) {
        return WiFi.localIP().toString().c_str();
    } else {
        return WiFi.softAPIP().toString().c_str();
    }
}


void WifiHandler::showWifiSettings() {
    if (this->isConnectedToWifi()) {
        display.showIpWithLabel(getIp(), CONNECTED_LABEL);
    } else {
        display.showIpWithLabel(getIp(), DEFAULT_WIFI_LABEL);
    }
}

void WifiHandler::resetSettings() {
    display.showMessage(RESETTING_WIFI_LABEL_UPPER, RESETTING_WIFI_LABEL_UPPER);
    filesystem::deleteFile(WIFI_CONFIG_FILE);
    this->connectedToWifi = false;
    WiFi.disconnect(true);
    this->init();
}



