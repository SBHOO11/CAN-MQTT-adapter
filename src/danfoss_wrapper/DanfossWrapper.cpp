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

std::string DanfossWrapper::convertCAN2MQTT(CAN_Msg &can_msg) {
    // Construct MQTT header from CAN id
    std::string MQTT_header{CAN_id_2_MQTT_header_map_[can_msg.can_id]};
    if (MQTT_header == "") {
        std::cerr << "CAN-id to MQTT mapping not found" << std::endl;
        throw Common::InvalidMapping();
    }

    // Construct MQTT payload form CAN data
    uint16_t MQTT_data{};
    ENCODE_2BYTES_TO_NUM16(can_msg.data[0], can_msg.data[1], MQTT_data);

    std::string MQTT_msg{};
    MQTT_msg = MQTT_header + "/" + std::to_string(MQTT_data);
    return MQTT_msg;
}

CAN_Msg DanfossWrapper::convertMQTT2CAN(std::string mqtt_msg) {
    // Split mqtt_msg into header and data
    std::string delimiter{"/"};
    size_t delimiter_pos = mqtt_msg.find(delimiter);
    std::string mqtt_header = mqtt_msg.substr(0, delimiter_pos);
    std::string mqtt_data = mqtt_msg.substr(delimiter_pos+1, mqtt_msg.length() - (delimiter_pos+1));

    // Construct CAN id from MQTT header
    std::map<uint, std::string>::iterator start_itr = CAN_id_2_MQTT_header_map_.begin();
    std::map<uint, std::string>::iterator end_itr = CAN_id_2_MQTT_header_map_.end();
    auto itr = std::find_if(start_itr, end_itr,
            [&mqtt_header](const std::pair<uint, std::string> &p) { return p.second == mqtt_header; });

    if (itr == end_itr) {
        std::cerr << "MQTT -> CANid mapping not found" << std::endl;
        throw Common::InvalidMapping();
    }

    CAN_Msg can_msg{};
    can_msg.can_id = itr->first;
    ENCODE_NUM16_TO_2BYTES(std::stoi(mqtt_data), can_msg.data[0], can_msg.data[1]);

    return can_msg;
}
