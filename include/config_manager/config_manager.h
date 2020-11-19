#ifndef CAN_MQTT_ADAPTER_CONFIG_MANAGER_H
#define CAN_MQTT_ADAPTER_CONFIG_MANAGER_H

#include <iostream>
#include <fstream>
#include "json/json.h"

class ConfigManager {
public:
    ConfigManager(std::string);
    Json::Value getMqttConfig() {return config["mqtt_config"];}; 
    Json::Value getAddrMapping() {return config["addr_mapping"];};

private:
    Json::Value config;
};

#endif //CAN_MQTT_ADAPTER_CONFIG_MANAGER_H
