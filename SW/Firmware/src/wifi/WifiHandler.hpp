//
// Created by jiri on 4.3.23.
//

#ifndef FIRMWARE_WIFIHANDLER_HPP
#define FIRMWARE_WIFIHANDLER_HPP
#include <ESP8266WiFi.h>
#include <string>


class WifiHandler {
private:
    static const IPAddress ipAddress;
    static const IPAddress gateway;
    static const IPAddress subnet;
    std::string ssid;
    std::string password;
    bool connectedToWifi;

private:
    void waitUntilConnectedToWifi();
public:
    void init();
    void setNewConfig(const std::string &newSsid, const std::string &newPassword);
    WifiHandler();

    [[nodiscard]] bool isConnectedToWifi() const;
};


#endif //FIRMWARE_WIFIHANDLER_HPP
