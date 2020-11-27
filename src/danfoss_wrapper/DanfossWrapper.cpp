//
// Created by shibinhoo on 22/6/20.
//

#include "DanfossWrapper.h"

MQTT_Msg DanfossWrapper::convertCAN2MQTT(CAN_Msg &can_msg) {
    // Construct MQTT topic from CAN id
    Json::Value::Members keys = addr_map_.getMemberNames();
    std::string mqtt_topic{""};
    for (std::string key : keys) {
        if (addr_map_[key].asInt() == can_msg.can_id) {
            mqtt_topic = key;
            break;
        }
    }

    if (mqtt_topic == "") {
        std::cerr << "CAN-id to MQTT mapping not found" << std::endl;
        throw Common::InvalidMapping();
    }

    // Construct MQTT payload form CAN data
    int16_t mqtt_payload_int16{};
    ENCODE_2BYTES_TO_NUM16(can_msg.data[0], can_msg.data[1], mqtt_payload_int16);

    return MQTT_Msg(mqtt_topic, std::to_string(mqtt_payload_int16));
}

CAN_Msg DanfossWrapper::convertMQTT2CAN(MQTT_Msg &mqtt_msg) {
    // Construct CAN id from MQTT header

    // Check if MQTT topic is defined in the list
    if (!addr_map_.isMember(mqtt_msg.topic)) {
        std::cerr << "MQTT to CANid mapping not found" << std::endl;
        throw Common::InvalidMapping();
    }

    CAN_Msg can_msg{};
    can_msg.can_id = addr_map_[mqtt_msg.topic].asInt();
    ENCODE_NUM16_TO_2BYTES(std::stoi(mqtt_msg.payload), can_msg.data[0], can_msg.data[1]);

    return can_msg;
}
