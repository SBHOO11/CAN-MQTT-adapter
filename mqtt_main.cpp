//
// Created by shibinhoo on 27/6/20.
//

#include <iostream>
#include "json/json.h"
#include "config_manager.h"
#include "mqtt.h"
#include "mqtt_common.h"
#include "Common.h"

using std::cout;
using std::cerr;
using std::endl;


void MQTT_WorkerThread(Json::Value mqtt_config) {

    // Parse json value to std::vector<std::string>
    std::vector<std::string> sub_topics;
    for (auto itr = mqtt_config["sub_topics"].begin(); itr != mqtt_config["sub_topics"].end(); itr++) {
        sub_topics.push_back(itr->asString());
    }
    

    // Initialize MQTT client
    MQTT_Config Config = MQTT_Config();
    Config.server_addr = mqtt_config["server_addr"].asString();
    Config.client_id = mqtt_config["client_id"].asString();\
    Config.sub_topics = sub_topics;
    Config.QOS = mqtt_config["qos"].asInt();

    MQTT_ITF mqttCli = MQTT_ITF(Config);

    if (mqttCli.start()) {
        cout << "[OK] MQTT client" << endl;
    }
    else {
        cerr << "[ERR] Unable to set up MQTT client" << endl;
        exit(1);
    }

    // Main function
    while (1) {
        if (!Common::MQTT_publish_q.empty()) {
            MQTT_Msg msg = Common::MQTT_publish_q.front();
            Common::MQTT_publish_q.pop();

            mqttCli.publish(msg);
        }

        if (mqttCli.is_msg_ready()) {
            Common::MQTT_receive_q.push(mqttCli.next_msg());
        }
    }
}
