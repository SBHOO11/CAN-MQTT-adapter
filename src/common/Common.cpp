//
// Created by shibinhoo on 28/6/20.
//

#include "Common.h"

// Initialize (static) queues
std::queue<std::string> Common::MQTT_publish_q{};
std::queue<std::string> Common::MQTT_receive_q{};
