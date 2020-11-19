//
// Created by shibinhoo on 24/6/20.
//

#include <iostream>
#include "mqtt.h"

using std::cout;
using std::endl;


MQTT_ITF::MQTT_ITF(const MQTT_Config &config) :
        config_(config),
        cliPtr_(new mqtt::async_client(config_.server_addr, config_.client_id)) {

    cout << "Initializing MQTT client with addr(" << config_.server_addr << "), "
              << "clientID(" << config_.client_id << ")" << endl;
}

bool MQTT_ITF::start() {
    cout << "Connecting to client...";

    try {
//        cliPtr_->set_message_callback(
//                static_cast<void (*)(mqtt::const_message_ptr)>(&message_recv_callback));
        cliPtr_->set_callback(Callback_);

        mqtt::token_ptr connTok = cliPtr_->connect();
        connTok->wait();
        cout << "OK" << endl;

        // Subscribe to topics
        for (std::string sub_topic_name : config_.sub_topics) {
            std::cout << sub_topic_name << std::endl;
            cliPtr_->subscribe(sub_topic_name, config_.QOS);
        }

        return true;
    }

    catch(const std::exception& e) {
        cout << "FAIL" << endl;
        std::cerr << "Error - " << e.what() << endl;
        return false;
    }
}

bool MQTT_ITF::publish(MQTT_Msg &msg) {
    cout << "Publishing - [" << msg.topic << "] - " << msg.payload << endl;
    mqtt::delivery_token_ptr  pubTok;
    pubTok = cliPtr_->publish(msg.topic.c_str(), msg.payload.c_str(), msg.payload.size(), config_.QOS, false);
}

MQTT_Msg MQTT_ITF::next_msg() {
    MQTT_Msg msg = msg_rx_q_.front();
    msg_rx_q_.pop();
    return msg;
}


// --------------------------------------------------------------------------------------------------
// Implementation of MQTT_ITF::Callback methods

void MQTT_ITF::Callback::connection_lost(const std::string &cause) {
    cout << "Connection lost" << endl;
    if (!cause.empty())
        cout << "\tcause: " << cause << endl;
}

void MQTT_ITF::Callback::delivery_complete(mqtt::delivery_token_ptr tok) {
    // cout << "Delivery complete for token: " << (tok ? tok->get_message_id() : -1) << endl;
}

void MQTT_ITF::Callback::message_arrived(mqtt::const_message_ptr msg) {
    MQTT_Msg m (msg->get_topic(), msg->get_payload());
    cout << "Received message - [" << m.topic << "] - " << m.payload << endl;
    msg_rx_q_.push(m);
}
