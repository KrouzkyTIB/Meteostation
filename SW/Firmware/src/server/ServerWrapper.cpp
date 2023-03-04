//
// Created by jiri on 4.3.23.
//

#include "ServerWrapper.hpp"
#include "filesystem/Filesystem.hpp"

#define PORT 80
#define STATS_JS_FILENAME "stats.js"
#define STATS_CSS_FILENAME "stats.css"
#define STATS_PAGE_FILENAME "stats.html"


ESP8266WebServer ServerWrapper::webServer(PORT);
std::string ServerWrapper::statsJsBuffer;
std::string ServerWrapper::statsCssBuffer;
std::string ServerWrapper::statsPageBuffer;
std::string ServerWrapper::wifiCssBuffer;
std::string ServerWrapper::wifiJsBuffer;
std::string ServerWrapper::wifiConfigPageBuffer;
WifiHandler *ServerWrapper::wifiHandler;

void ServerWrapper::init(WifiHandler *wifiHandler) {
    ServerWrapper::wifiHandler = wifiHandler;
    statsCssBuffer = filesystem::readFile(STATS_CSS_FILENAME);
    statsJsBuffer = filesystem::readFile(STATS_JS_FILENAME);
    statsPageBuffer = filesystem::readFile(STATS_PAGE_FILENAME);
    webServer.on("/", serveHtmlPage);
    webServer.on("/stats.js", serveStatsJs);
    webServer.on("/stats.css", serveStatsCss);
    webServer.begin();
}

void ServerWrapper::serveHtmlPage() {
    Serial.println("Serving html page");
    webServer.send(200, "text/html", statsPageBuffer.c_str(), statsPageBuffer.size());
}

void ServerWrapper::serveStatsJs() {
    webServer.send(200, "text/javascript", statsJsBuffer.c_str(), statsJsBuffer.size());
}

void ServerWrapper::serveStatsCss() {
    webServer.send(200, "text/css", statsCssBuffer.c_str(), statsCssBuffer.size());
}

void ServerWrapper::handleClient() {
    webServer.handleClient();
}





