//
// Created by shibinhoo on 24/6/20.
//

#include <iostream>
#include "mqtt/async_client.h"
#include "mqtt.h"

//#define NORMAL

int main(int argc, char** argv) {
    std::cout << "Hello world from MQTT" << std::endl;

    MQTT_Config myConfig = MQTT_Config();
    myConfig.server_addr = "tcp://localhost:1883";
    myConfig.client_id = "CAN-MQTT-adapter";
    myConfig.topic = "CAN-MQTT";
    myConfig.payload_size = 1;
    myConfig.QOS = 1;

#ifdef NORMAL
    MQTT_ITF myMQTT = MQTT_ITF(myConfig);
    myMQTT.connect();
    std::string message{"Hi there"};
    for (int i=0; i!=10; i++) {
        myMQTT.publish(message);
        std::cout << "next" << std::endl;
    }

#else
    mqtt::async_client_ptr myPtr;
    mqtt::async_client client(myConfig.server_addr, myConfig.client_id);
    myPtr = static_cast<const std::shared_ptr<mqtt::async_client>>(&client);
    mqtt::connect_options connOpts;
    std::cout << "Connecting...";
    mqtt::token_ptr connTok = myPtr->connect(connOpts);
    connTok->wait();
    std::cout << "DONE" << std::endl;

    std::string data {"Hello motherfuckers, from ptr"};

    for (int i=0; i!=10; i++) {
        std::cout << "Publishing...";
        mqtt::delivery_token_ptr pubTok;
        pubTok = myPtr->publish(myConfig.topic, data.c_str(), data.size(), myConfig.QOS, false);
        std::cout << "Done" << std::endl;
    }

    std::string data1 {"Hello motherfuckers, from client"};

    for (int i=0; i!=10; i++) {
        std::cout << "Publishing...";
        mqtt::delivery_token_ptr pubTok;
        pubTok = client.publish(myConfig.topic, data1.c_str(), data1.size(), myConfig.QOS, false);
        std::cout << "Done" << std::endl;
    }

    myPtr->disconnect();

#endif


    return 1;
}

