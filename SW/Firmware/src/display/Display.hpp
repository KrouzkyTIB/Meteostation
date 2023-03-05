//
// Created by jiri on 1.3.23.
//

#ifndef FIRMWARE_DISPLAY_HPP
#define FIRMWARE_DISPLAY_HPP

#include <LiquidCrystal_I2C.h>
#include "../sensor/Sensor.hpp"
#include <iomanip>
#include <sstream>
#include <string>

class Display {
private:
    static const std::string INDOOR_LABEL;
    static const std::string OUTDOOR_LABEL;
    LiquidCrystal_I2C display;
    Sensor &indoorSensor;
    Sensor &outdoorSensor;
    uint64_t lastUpdateMillis;
    uint64_t showIpUntilMillis;
private:
    static std::string formatValue(float value, int precision);

    static std::string prepareDataForLine(const std::string &label, float temperature, float humidity);

    static std::string centerText(const char *string);


public:
    Display(Sensor &indoorSensor, Sensor &outdoorSensor);

    void turnBacklightOff();

    void turnBacklightOn();

    void update();

    void init();

    void showIpWithLabel(const std::string &ip, const char *label);
    void showMessage(const char * upperLine, const char * lowerLine);

};


#endif //FIRMWARE_DISPLAY_HPP
