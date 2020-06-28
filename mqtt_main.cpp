//
// Created by shibinhoo on 27/6/20.
//

#include <iostream>
#include "mqtt.h"
#include "Common.h"

using std::cout;
using std::cerr;
using std::endl;


void MQTT_WorkerThread() {

    // Initialize MQTT client
    MQTT_Config Config = MQTT_Config();
    Config.server_addr = "tcp://localhost:1883";
    Config.client_id = "CAN-MQTT-adapter";
    Config.pub_topic = "CAN-MQTT-PUB";
    Config.sub_topic = "CAN-MQTT-SUB";
    Config.QOS = 1;

    MQTT_ITF mqttCli = MQTT_ITF(Config);

    if (mqttCli.start()) {
        cout << "Successfully set up MQTT client" << endl;
    }
    else {
        // TODO: not sure how to handle yet
        cerr << "Unable to set up MQTT client" << endl;
    }

    // Main function
    while (1) {
        if (!Common::MQTT_publish_q.empty()) {
            std::string msg{Common::MQTT_publish_q.front()};
            Common::MQTT_publish_q.pop();

            mqttCli.publish(msg);
        }
    }
}
