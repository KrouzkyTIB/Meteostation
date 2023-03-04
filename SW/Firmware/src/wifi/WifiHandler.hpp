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
public:
    void init();
};


#endif //FIRMWARE_WIFIHANDLER_HPP
