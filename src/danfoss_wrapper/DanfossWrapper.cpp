//
// Created by shibinhoo on 22/6/20.
//

#include <iostream>
#include "DanfossWrapper.h"

std::map<uint, std::string> DanfossWrapper::CAN_id_2_MQTT_header_map_ = {
        {10, "Joystick_X"},
        {11, "Joystick_Y"},
        {12, "Joystick_Z"}
};

MQTT_Msg DanfossWrapper::convertCAN2MQTT(CAN_Msg &can_msg) {
    // Construct MQTT topic from CAN id
    std::string mqtt_topic = CAN_id_2_MQTT_header_map_[can_msg.can_id];
    if (mqtt_topic == "") {
        std::cerr << "CAN-id to MQTT mapping not found" << std::endl;
        throw Common::InvalidMapping();
    }

    // Construct MQTT payload form CAN data
    uint16_t mqtt_payload_uint16{};
    ENCODE_2BYTES_TO_NUM16(can_msg.data[0], can_msg.data[1], mqtt_payload_uint16);

    return MQTT_Msg(mqtt_topic, std::to_string(mqtt_payload_uint16));
}

CAN_Msg DanfossWrapper::convertMQTT2CAN(MQTT_Msg &mqtt_msg) {
    // Construct CAN id from MQTT header

    // Check if MQTT topic is defined in the list
    auto start_itr = CAN_id_2_MQTT_header_map_.begin();
    auto end_itr = CAN_id_2_MQTT_header_map_.end();
    auto itr = start_itr;
    for ( ; itr != end_itr; itr++)
    {
        if (itr->second == mqtt_msg.topic)
            break;
    }

    // Logically it should always be found, just in case
    if (itr == end_itr) {
        std::cerr << "MQTT -> CANid mapping not found" << std::endl;
        throw Common::InvalidMapping();
    }

    CAN_Msg can_msg{};
    can_msg.can_id = itr->first;
    ENCODE_NUM16_TO_2BYTES(std::stoi(mqtt_msg.payload), can_msg.data[0], can_msg.data[1]);

    return can_msg;
}
