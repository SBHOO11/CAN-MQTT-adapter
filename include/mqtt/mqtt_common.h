#ifndef CAN_MQTT_ADAPTER_MQTT_COMMON_H
#define CAN_MQTT_ADAPTER_MQTT_COMMON_H

#include <string>

class MQTT_Msg {    
public:
    MQTT_Msg(std::string t, std::string p) : topic(t), payload(p) {};

    std::string topic;
    std::string payload;

};

#endif