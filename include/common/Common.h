//
// Created by shibinhoo on 28/6/20.
//

#ifndef CAN_MQTT_ADAPTER_COMMON_H
#define CAN_MQTT_ADAPTER_COMMON_H

#include <queue>
#include <string>
#include "CAN_common.h"
#include "mqtt_common.h"


class Common {
public:
    static std::queue<MQTT_Msg> MQTT_publish_q;
    static std::queue<MQTT_Msg> MQTT_receive_q;
    static std::queue<CAN_Msg> CAN_publish_q;
    static std::queue<CAN_Msg> CAN_receive_q;

    class InvalidMapping : public std::exception {
    public:
        const char* what() const throw() {
            return "Invalid mapping of CAN_id and MQTT_header\n";
        }
    };
};

#endif //CAN_MQTT_ADAPTER_COMMON_H

