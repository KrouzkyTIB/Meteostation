//
// Created by jiri on 4.3.23.
//

#ifndef FIRMWARE_SERVERWRAPPER_HPP
#define FIRMWARE_SERVERWRAPPER_HPP

#include <ESP8266WebServer.h>
#include "wifi/WifiHandler.hpp"


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


private:
    static void serveHtmlPage();
    static void serveStatsCss();
    static void serveStatsJs();
public:
    static void init(WifiHandler *wifiHandler);
    static void handleClient();
};


#endif //FIRMWARE_SERVERWRAPPER_HPP
