//
// Created by shibinhoo on 24/6/20.
//

#include <iostream>
#include "mqtt.h"


using std::cout;
using std::endl;


int main(int argc, char** argv) {
    cout << "Hello world from MQTT" << endl;

    MQTT_Config Config = MQTT_Config();
    Config.server_addr = "tcp://localhost:1883";
    Config.client_id = "CAN-MQTT-adapter";
    Config.topic = "CAN-MQTT";
    Config.payload_size = 1;
    Config.QOS = 1;

    MQTT_ITF M_Obj = MQTT_ITF(Config);
    M_Obj.connect();

    std::string message {"Hello from the other side."};
    M_Obj.publish(message);

    return 0;
}
