//
// Created by shibinhoo on 24/6/20.
//

#include <iostream>
#include "mqtt.h"
#include "mqtt/async_client.h"

using std::cout;
using std::endl;


MQTT_ITF::MQTT_ITF(const MQTT_Config &config) :
        config_(config),
        cliPtr_(new mqtt::async_client(config_.server_addr, config_.client_id)) {

    cout << "Initializing MQTT client with addr(" << config_.server_addr << "), "
              << "clientID(" << config_.client_id << ")" << endl;

    cliPtr_->set_callback(Callback_);

}

bool MQTT_ITF::connect() {
    cout << "Connecting to client..." << endl;

    try {
        mqtt::token_ptr connTok = cliPtr_->connect();
        connTok->wait();
        return true;
    }

    catch(const std::exception& e) {
        std::cerr << "Error - " << e.what() << endl;
        return false;
    }
}

bool MQTT_ITF::publish(std::string &message) {
    cout << "Publishing " << message << endl;
    mqtt::delivery_token_ptr  pubTok;

    pubTok = cliPtr_->publish(config_.topic, message.c_str(), message.size(), config_.QOS, false);
}

bool MQTT_ITF::subscribe() {}

// --------------------------------------------------------------------------------------------------
// Implementation of MQTT_ITF::Callback methods

void MQTT_ITF::Callback::connected(const std::string &cause) {
    cout << "Connection established" << endl;
}

void MQTT_ITF::Callback::connection_lost(const std::string &cause) {
    cout << "Connection lost" << endl;
    if (!cause.empty())
        cout << "\tcause: " << cause << endl;
}

void MQTT_ITF::Callback::delivery_complete(mqtt::delivery_token_ptr tok) {
    cout << "Delivery complete for token: " << (tok ? tok->get_message_id() : -1) << endl;
}
