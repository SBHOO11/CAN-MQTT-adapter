//
// Created by shibinhoo on 28/6/20.
//

#include "Common.h"

// Initialize (static) queues
std::queue<MQTT_Msg> Common::MQTT_publish_q{};
std::queue<MQTT_Msg> Common::MQTT_receive_q{};
std::queue<CAN_Msg> Common::CAN_publish_q{};
std::queue<CAN_Msg> Common::CAN_receive_q{};
