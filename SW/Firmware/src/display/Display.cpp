//
// Created by jiri on 1.3.23.
//

#include "Display.hpp"


#define DISPLAY_WIDTH 16
#define DISPLAY_HEIGHT 2
#define DISPLAY_ADDRESS 0x27
#define TEMP_PRECISION 1
#define LABEL_WIDTH 4
#define TEMPERATURE_WIDTH 5
#define HUMIDITY_WIDTH 3
#define HUMIDITY_PRECISION 0
#define INDOOR_DISPLAY_LINE 0
#define OUTDOOR_DISPLAY_LINE 1
#define DEGREE_CHAR ((char)0xDF)
#define REFRESH_RATE_MS 1000
#define WIFI_SHOW_DELAY 15000L


const std::string Display::INDOOR_LABEL = "In";
const std::string Display::OUTDOOR_LABEL = "Out";

Display::Display(Sensor &indoorSensor, Sensor &outdoorSensor) : display(DISPLAY_ADDRESS,
                                                                        DISPLAY_WIDTH,
                                                                        DISPLAY_HEIGHT),
                                                                indoorSensor(indoorSensor),
                                                                outdoorSensor(outdoorSensor) {
    this->lastUpdateMillis = 0;
    this->showIpUntilMillis = 0;
}

std::string Display::formatValue(float value, int precision) {
    std::stringstream stream;
    stream << std::fixed << std::setprecision(precision) << value;
    return stream.str();
}

std::string Display::prepareDataForLine(const std::string &label, float temperature, float humidity) {
    std::stringstream stringStream;
    stringStream << std::setw(LABEL_WIDTH) << std::left << label;
    stringStream << std::setw(TEMPERATURE_WIDTH) << std::right << formatValue(temperature, TEMP_PRECISION)
                 << DEGREE_CHAR << "C";
    stringStream << " ";
    stringStream << std::setw(HUMIDITY_WIDTH) << std::right << formatValue(humidity, HUMIDITY_PRECISION);
    stringStream << "%";

    return stringStream.str();
}

void Display::update() {
    if (this->lastUpdateMillis + REFRESH_RATE_MS <= millis() || millis() < this->lastUpdateMillis) {
        if (millis() > this->showIpUntilMillis) {
            this->lastUpdateMillis = millis();
            Serial.printf("Update\n");
            std::string indoorDataLine = prepareDataForLine(INDOOR_LABEL,
                                                            this->indoorSensor.getTemperature(),
                                                            this->indoorSensor.getHumidity());
            std::string outdoorDataLine = prepareDataForLine(OUTDOOR_LABEL,
                                                             this->outdoorSensor.getTemperature(),
                                                             this->outdoorSensor.getHumidity());
            display.setCursor(0, INDOOR_DISPLAY_LINE);
            display.printstr(indoorDataLine.c_str());
            display.setCursor(0, OUTDOOR_DISPLAY_LINE);
            display.printstr(outdoorDataLine.c_str());
            this->showIpUntilMillis = 0;
        }
    }
}

void Display::turnBacklightOff() {
    display.noBacklight();
}

void Display::turnBacklightOn() {
    display.backlight();
}

void Display::init() {
    display.init();
    display.clear();
}

void Display::showIpWithLabel(const std::string &ip, const char *label) {
    this->showIpUntilMillis = millis() + WIFI_SHOW_DELAY;
    display.clear();
    display.setCursor(0, 0);
    display.printstr(centerText(label).c_str());
    display.setCursor(0, 1);
    display.printstr(centerText(ip.c_str()).c_str());
}

std::string Display::centerText(const char *string) {
    std::string originalString(string);
    std::stringstream buffer;
    buffer << std::setw((int) (DISPLAY_WIDTH - originalString.size()) / 2) << " ";
    buffer << originalString;
    return buffer.str();

}






