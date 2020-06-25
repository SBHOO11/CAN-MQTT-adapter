//
// Created by shibinhoo on 24/6/20.
//

#include <iostream>
#include "mqtt.h"
#include "mqtt/async_client.h"

//MQTT_ITF(MQTT_Config &config):config_(config) {};

bool MQTT_ITF::connect() {
    std::cout << "Initializing client at '" << config_.server_addr << "'..." << std::endl;
    mqtt::async_client client_(config_.server_addr, config_.client_id);
    mqtt::connect_options connOpts;

    try {
        std::cout << "Connecting...";
        mqtt::token_ptr connTok = client_.connect(connOpts);
        connTok->wait();
        std::cout << "Connected." << std::endl;
        return true;
    }

    catch(const std::exception& e) {
        std::cerr << "Error - " << e.what() << std::endl;
        return false;
    }
}

bool MQTT_ITF::publish(std::string &message) {
    std::cout << "Publishing " << message << std::endl;
    mqtt::delivery_token_ptr  pubTok;

    pubTok = client_->publish(config_.topic, message.c_str(), message.size(), config_.QOS, false);
    std::cout << "Published" << std::endl;
}

bool MQTT_ITF::subscribe() {}
