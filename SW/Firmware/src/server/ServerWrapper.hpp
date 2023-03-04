//
// Created by jiri on 4.3.23.
//

#ifndef FIRMWARE_SERVERWRAPPER_HPP
#define FIRMWARE_SERVERWRAPPER_HPP

#include <ESP8266WebServer.h>
#include "wifi/WifiHandler.hpp"
#include "sensor/Sensor.hpp"


class ServerWrapper {

private:
    static ESP8266WebServer webServer;
    static std::string statsPageBuffer;
    static std::string statsCssBuffer;
    static std::string statsJsBuffer;
    static std::string wifiConfigPageBuffer;
    static std::string wifiCssBuffer;
    static std::string wifiJsBuffer;
    static WifiHandler *wifiHandler;
    static Sensor *indoorSensor;
    static Sensor *outdoorSensor;

private:
    static void serveHtmlPage();
    static void serveStatsCss();
    static void serveStatsJs();
    static void replace(std::string &buffer, std::string pattern, std::string newValue);
public:
    static void init(WifiHandler *wifiHandler, Sensor *indoorSensor, Sensor *outdoorSensor);
    static void handleClient();
    static std::string truncateFloatToTwoDigits(float value);
};


#endif //FIRMWARE_SERVERWRAPPER_HPP
