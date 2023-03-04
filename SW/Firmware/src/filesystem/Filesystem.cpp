//
// Created by jiri on 4.3.23.
//

#include "Filesystem.hpp"
#include "LittleFS.h"


void filesystem::init() {
    LittleFS.begin();
}

std::vector<std::string> filesystem::readAllLinesFromFile(const char *filename) {
    std::vector<std::string> lines;
    File file = LittleFS.open(filename, "r");
    int readChar = file.read();
    std::string buffer;
    while (readChar != EOF) {
        if (readChar == '\n') {
            lines.emplace_back(buffer);
            buffer.clear();
        } else {
            buffer += (char) readChar;
        }
        readChar = file.read();
    }
    file.close();
    return lines;
}


std::string filesystem::readFile(const char *filename) {
    std::string buffer;
    File file = LittleFS.open(filename, "r");
    int readChar = file.read();
    while (readChar != EOF) {
        buffer += (char) readChar;
        readChar = file.read();
    }
    file.close();
    return buffer;
}

bool filesystem::doesFileExists(const char *filename) {
    return LittleFS.exists(filename);
}
