//
// Created by jiri on 4.3.23.
//

#ifndef FIRMWARE_FILESYSTEM_HPP
#define FIRMWARE_FILESYSTEM_HPP

#include <string>
#include <vector>

namespace filesystem{
    void init();
    std::vector<std::string> readAllLinesFromFile(const char * filename);
    std::string readFile(const char * filename);
    bool doesFileExists(const char * filename);
    void saveLinesToFile(const char * filename, std::vector<std::string> &lines);
    void deleteFile(const char * name);
}


#endif //FIRMWARE_FILESYSTEM_HPP
