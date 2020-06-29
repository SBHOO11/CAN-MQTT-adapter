//
// Created by shibinhoo on 28/6/20.
//

#ifndef CAN_MQTT_ADAPTER_COMMON_H
#define CAN_MQTT_ADAPTER_COMMON_H

#include <queue>
#include <string>
#include "CAN_common.h"


class Common {
public:
    static std::queue<std::string> MQTT_publish_q;
    static std::queue<std::string> MQTT_receive_q;
    static std::queue<CAN_Msg> CAN_publish_q;
    static std::queue<CAN_Msg> CAN_receive_q;

};

#endif //CAN_MQTT_ADAPTER_COMMON_H

