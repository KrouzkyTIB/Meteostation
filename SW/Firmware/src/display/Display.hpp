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

private:
    static std::string formatValue(float value, int precision);
    static std::string prepareDataForLine(const std::string &label, float temperature, float humidity);


public:
    Display(Sensor &indoorSensor, Sensor &outdoorSensor);
    void turnBacklightOff();
    void turnBacklightOn();
    void update();
    void init();


};


#endif //FIRMWARE_DISPLAY_HPP
