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
#define CONFIG_PAGE_FILENAME "wifiConfig.html"
#define CONFIG_CSS_FILENAME "wifiConfig.css"
#define INDOOR_TEMPERATURE_TAG std::string("<%=indoorTemperature%>")
#define INDOOR_HUMIDITY_TAG std::string("<%=indoorHumidity%>")
#define OUTDOOR_TEMPERATURE_TAG std::string("<%=outdoorTemperature%>")
#define OUTDOOR_HUMIDITY_TAG std::string("<%=outdoorHumidity%>")
#define DISPLAY_BACKLIGHT_TAG std::string("<%=lcdBacklight%>")
#define TURN_BACKLIGHT_ON "Zapnout podsvícení"
#define TURN_BACKLIGHT_OFF "Vypnout podsvícení"

ESP8266WebServer ServerWrapper::webServer(PORT);
std::string ServerWrapper::statsJsBuffer;
std::string ServerWrapper::statsCssBuffer;
std::string ServerWrapper::statsPageBuffer;
std::string ServerWrapper::wifiConfigCssBuffer;
std::string ServerWrapper::wifiConfigPageBuffer;
WifiHandler *ServerWrapper::wifiHandler;
Sensor *ServerWrapper::indoorSensor;
Sensor *ServerWrapper::outdoorSensor;
Display *ServerWrapper::display;


void ServerWrapper::init(WifiHandler *wifiHandler, Sensor *indoorSensor, Sensor *outdoorSensor, Display *display) {
    ServerWrapper::wifiHandler = wifiHandler;
    ServerWrapper::outdoorSensor = outdoorSensor;
    ServerWrapper::indoorSensor = indoorSensor;
    ServerWrapper::display = display;
    statsCssBuffer = filesystem::readFile(STATS_CSS_FILENAME);
    statsJsBuffer = filesystem::readFile(STATS_JS_FILENAME);
    statsPageBuffer = filesystem::readFile(STATS_PAGE_FILENAME);
    wifiConfigPageBuffer = filesystem::readFile(CONFIG_PAGE_FILENAME);
    wifiConfigCssBuffer = filesystem::readFile(CONFIG_CSS_FILENAME);
    webServer.on("/", HTTPMethod::HTTP_GET, serveHtmlPage);
    webServer.on("/", HTTPMethod::HTTP_POST, setWifiCredentials);
    webServer.on("/stats.js", HTTPMethod::HTTP_GET, serveStatsJs);
    webServer.on("/stats.css", HTTPMethod::HTTP_GET, serveStatsCss);
    webServer.on("/wifiConfig.css", HTTPMethod::HTTP_GET, serveConfigCss);
    webServer.on("/toggle-lcd", HTTPMethod::HTTP_POST, toggleDisplayBacklight);
    webServer.on("/reset-wifi", HTTPMethod::HTTP_POST, handleResetWifi);
    webServer.begin();
}

void ServerWrapper::serveHtmlPage() {
    if (ServerWrapper::wifiHandler->isConnectedToWifi()) {
        serveStatsPage();
    } else {
        serveConfigPage();
    }
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

void ServerWrapper::serveStatsPage() {
    std::string pageWithData(statsPageBuffer);
    replace(pageWithData, INDOOR_TEMPERATURE_TAG, truncateFloatToTwoDigits(indoorSensor->getTemperature()));
    replace(pageWithData, INDOOR_HUMIDITY_TAG, truncateFloatToTwoDigits(indoorSensor->getHumidity()));
    replace(pageWithData, OUTDOOR_TEMPERATURE_TAG, truncateFloatToTwoDigits(outdoorSensor->getTemperature()));
    replace(pageWithData, OUTDOOR_HUMIDITY_TAG, truncateFloatToTwoDigits(outdoorSensor->getHumidity()));
    replace(pageWithData, DISPLAY_BACKLIGHT_TAG, display->isBacklightOn() ? TURN_BACKLIGHT_OFF : TURN_BACKLIGHT_ON);
    webServer.send(200, "text/html", pageWithData.c_str(), pageWithData.size());
}

void ServerWrapper::serveConfigPage() {
    webServer.send(200, "text/html", wifiConfigPageBuffer.c_str(), wifiConfigPageBuffer.size());
}

void ServerWrapper::serveConfigCss() {
    webServer.send(200, "text/css", wifiConfigCssBuffer.c_str(), wifiConfigCssBuffer.size());
}

void ServerWrapper::setWifiCredentials() {

    if (!webServer.arg("ssid").isEmpty()) {
        std::string ssid = webServer.arg("ssid").c_str();
        std::string password = webServer.arg("password").c_str();
        wifiHandler->setNewConfig(ssid, password);
    } else {
        serveConfigPage();
    }
}

void ServerWrapper::toggleDisplayBacklight() {
    display->toggleBacklight();
    webServer.send(204, "application/json", "");
}

void ServerWrapper::handleResetWifi() {
    wifiHandler->resetSettings();
}


