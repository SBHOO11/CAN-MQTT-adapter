//
// Created by shibinhoo on 24/6/20.
//

#ifndef CAN_MQTT_ADAPTER_MQTT_CONFIG_H
#define CAN_MQTT_ADAPTER_MQTT_CONFIG_H

#include <string>

class MQTT_Config {
public:
    MQTT_Config() {};
    std::string server_addr;
    std::string client_id;
    std::string topic;
    int payload_size{};
    int QOS{};
};

#endif //CAN_MQTT_ADAPTER_MQTT_CONFIG_H
