//
// Created by shibinhoo on 27/6/20.
//

#include <iostream>
#include <chrono>
#include "mqtt.h"

using std::cout;
using std::cerr;
using std::endl;


void MQTT_ClientTask(MQTT_ITF& cli);

int startMQTTMain () {
    MQTT_Config Config = MQTT_Config();
    Config.server_addr = "tcp://localhost:1883";
    Config.client_id = "CAN-MQTT-adapter";
    Config.pub_topic = "CAN-MQTT-PUB";
    Config.sub_topic = "CAN-MQTT-SUB";
    Config.payload_size = 1;
    Config.QOS = 1;

    MQTT_ITF mqttCli = MQTT_ITF(Config);

    cout << "going in" << endl;
    if (mqttCli.start()) {
        cout << "Successfully set up MQTT client" << endl;
    }
    else {
        cerr << "Unable to set up MQTT client" << endl;
        return -1;
    }
    cout << "wtf?" << endl;

    std::thread thread(MQTT_ClientTask, std::ref(mqttCli));

    thread.join();
}

void MQTT_ClientTask(MQTT_ITF &cli) {

    int count = 0;
    std::string message;
    cout << "mqtt client thread" << endl;
    while (true) {
        message = "hello" + std::to_string(count);
        cli.publish(message);
        count++;
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
}