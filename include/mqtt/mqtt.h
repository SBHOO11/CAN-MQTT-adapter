//
// Created by shibinhoo on 24/6/20.
//

#ifndef CAN_MQTT_ADAPTER_MQTT_H
#define CAN_MQTT_ADAPTER_MQTT_H

#include <iostream>
#include "mqtt_config.h"
#include "mqtt/async_client.h"

class MQTT_ITF {
public:
    MQTT_ITF(MQTT_Config &config) : config_(config){};
    bool connect();
    bool publish(std::string &message);
    bool subscribe();
private:
    MQTT_Config config_;
    std::shared_ptr<mqtt::async_client> client_;
};


#endif //CAN_MQTT_ADAPTER_MQTT_H
