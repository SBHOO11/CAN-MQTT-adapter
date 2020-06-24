//
// Created by shibinhoo on 21/6/20.
//

#ifndef CAN_MQTT_ADAPTER_CAN_COMMON_H
#define CAN_MQTT_ADAPTER_CAN_COMMON_H

#include <array>

#define CAN_PAYLOAD_LENGTH 8

class CANData {
public:
    uint can_id;
    std::array<uint, 8> data;
};

#endif //CAN_MQTT_ADAPTER_CAN_COMMON_H
