#include "config_manager.h"

ConfigManager::ConfigManager(std::string filename) {
    std::ifstream config_file("../config.json");

    // Check if file exists
    if (!config_file) {
        std::cerr << "Unable to read config.json, exit program..." << std::endl;
        exit(1);
    }

    Json::CharReaderBuilder rbuilder;
    std::string err;

    // Parse json, and check if parsing is successful
    bool parsed = Json::parseFromStream(rbuilder, config_file, &config, &err);
    if (!parsed) {
        std::cerr << "Unable to parse config (" << err << ")" << std::endl;
        std::cerr << "Exit program..." << std::endl;
        exit(1);
    }

    config_file.close();
}