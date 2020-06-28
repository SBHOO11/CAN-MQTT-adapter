//
// Created by shibinhoo on 24/6/20.
//

#ifndef CAN_MQTT_ADAPTER_MQTT_H
#define CAN_MQTT_ADAPTER_MQTT_H

#include <iostream>
#include <queue>
#include <string>
#include "mqtt_config.h"
#include "mqtt/async_client.h"


class MQTT_ITF {
public:

    MQTT_ITF(const MQTT_Config &config);

    bool start();
    bool publish(std::string &message);
    bool is_msg_ready() { return !msg_rx_q_.empty(); };
    std::string next_msg();

private:
    MQTT_Config config_;
    mqtt::async_client_ptr cliPtr_;
    inline static std::queue<std::string> msg_rx_q_{};   // ask Gio why this static is needed

    class Callback : public virtual mqtt::callback {
    public:
        void connection_lost(const std::string& cause) override;
        void delivery_complete(mqtt::delivery_token_ptr tok) override;
        void message_arrived(mqtt::const_message_ptr msg) override;
    };

    Callback Callback_;
};


#endif //CAN_MQTT_ADAPTER_MQTT_H
