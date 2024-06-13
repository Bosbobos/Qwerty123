#include "ConfigManager.h"
#include <fstream>

std::string GetDbConnectionString() {
    std::ifstream configFile("./DbConf.txt");
    if (!configFile.is_open()) {
        throw std::runtime_error("Cannot open DbConf.txt");
    }

    std::string line;
    std::getline(configFile, line);
    configFile.close();

    std::string prefix = "db_connection_string=";
    if (line.compare(0, prefix.length(), prefix) == 0) {
        return line.substr(prefix.length());
    } else {
        throw std::runtime_error("Invalid configuration file format");
    }
}
