//
// Created by jiri on 4.3.23.
//

#include "ServerWrapper.hpp"
#include "filesystem/Filesystem.hpp"
#include <iomanip>

#define PORT 80
#define STATS_JS_FILENAME "stats.js"
#define STATS_CSS_FILENAME "stats.css"
#define STATS_PAGE_FILENAME "stats.html"
#define INDOOR_TEMPERATURE_TAG std::string("<%=indoorTemperature%>")
#define INDOOR_HUMIDITY_TAG std::string("<%=indoorHumidity%>")
#define OUTDOOR_TEMPERATURE_TAG std::string("<%=outdoorTemperature%>")
#define OUTDOOR_HUMIDITY_TAG std::string("<%=outdoorHumidity%>")

ESP8266WebServer ServerWrapper::webServer(PORT);
std::string ServerWrapper::statsJsBuffer;
std::string ServerWrapper::statsCssBuffer;
std::string ServerWrapper::statsPageBuffer;
std::string ServerWrapper::wifiCssBuffer;
std::string ServerWrapper::wifiJsBuffer;
std::string ServerWrapper::wifiConfigPageBuffer;
WifiHandler *ServerWrapper::wifiHandler;
Sensor *ServerWrapper::indoorSensor;
Sensor *ServerWrapper::outdoorSensor;


void ServerWrapper::init(WifiHandler *wifiHandler, Sensor *indoorSensor, Sensor *outdoorSensor) {
    ServerWrapper::wifiHandler = wifiHandler;
    ServerWrapper::outdoorSensor = outdoorSensor;
    ServerWrapper::indoorSensor = indoorSensor;
    statsCssBuffer = filesystem::readFile(STATS_CSS_FILENAME);
    statsJsBuffer = filesystem::readFile(STATS_JS_FILENAME);
    statsPageBuffer = filesystem::readFile(STATS_PAGE_FILENAME);
    webServer.on("/", serveHtmlPage);
    webServer.on("/stats.js", serveStatsJs);
    webServer.on("/stats.css", serveStatsCss);
    webServer.begin();
}

void ServerWrapper::serveHtmlPage() {
    std::string pageWithData(statsPageBuffer);
    replace(pageWithData, INDOOR_TEMPERATURE_TAG, truncateFloatToTwoDigits(indoorSensor->getTemperature()));
    replace(pageWithData, INDOOR_HUMIDITY_TAG, truncateFloatToTwoDigits(indoorSensor->getHumidity()));
    replace(pageWithData, OUTDOOR_TEMPERATURE_TAG, truncateFloatToTwoDigits(outdoorSensor->getTemperature()));
    replace(pageWithData, OUTDOOR_HUMIDITY_TAG, truncateFloatToTwoDigits(outdoorSensor->getHumidity()));
    webServer.send(200, "text/html", pageWithData.c_str(), pageWithData.size());
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

void ServerWrapper::replace(std::string &buffer, std::string pattern, std::string newValue) {
    size_t position = buffer.find(std::string(pattern));
    buffer.replace(position, pattern.size(), newValue);
}

std::string ServerWrapper::truncateFloatToTwoDigits(float value) {
    Serial.println(value);
    std::stringstream stringstream;
    stringstream << std::fixed << std::setprecision(2) << std::setw(5) << value;
    return stringstream.str();
}



