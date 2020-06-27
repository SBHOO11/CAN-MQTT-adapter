//
// Created by shibinhoo on 24/6/20.
//

#ifndef CAN_MQTT_ADAPTER_MQTT_H
#define CAN_MQTT_ADAPTER_MQTT_H

#include <iostream>
#include "mqtt_config.h"
#include "mqtt/async_client.h"

class MQTT_ITF {
public:

    MQTT_ITF(const MQTT_Config &config);

    bool start();
    bool publish(std::string &message);

private:
    MQTT_Config config_;
    mqtt::async_client_ptr cliPtr_;

    class Callback : public virtual mqtt::callback {
    public:
        void connection_lost(const std::string& cause) override;
        void delivery_complete(mqtt::delivery_token_ptr tok) override;
        void message_arrived(mqtt::const_message_ptr msg) override;
    };

    Callback Callback_;
};


#endif //CAN_MQTT_ADAPTER_MQTT_H
