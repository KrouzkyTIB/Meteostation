//
// Created by jiri on 4.3.23.
//

#ifndef FIRMWARE_WIFIHANDLER_HPP
#define FIRMWARE_WIFIHANDLER_HPP

#include <ESP8266WiFi.h>
#include <string>
#include "display/Display.hpp"


class WifiHandler {
private:
    static const IPAddress ipAddress;
    static const IPAddress gateway;
    static const IPAddress subnet;
    std::string ssid;
    std::string password;
    bool connectedToWifi;
    Display &display;

private:
    void waitUntilConnectedToWifi();
    void showWifiSettings();

public:
    void init();
    void setNewConfig(const std::string &newSsid, const std::string &newPassword);
    void resetSettings();

    explicit WifiHandler(Display &display);
    WifiHandler() = delete;

    [[nodiscard]] bool isConnectedToWifi() const;

    [[nodiscard]] std::string getIp() const;
};


#endif //FIRMWARE_WIFIHANDLER_HPP
