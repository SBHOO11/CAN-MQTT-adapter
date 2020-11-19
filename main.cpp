//
// Created by shibinhoo on 27/6/20.
//

#include <iostream>
#include <thread>
#include <chrono>
#include "json/json.h"
#include <config_manager.h>
#include "Common.h"
#include "CAN_common.h"
#include "DanfossWrapper.h"

using std::cout;
using std::endl;


void MQTT_WorkerThread(Json::Value);
void CANBusWorkerThread(Json::Value);

int main(int argc, char** argv) {
    ConfigManager config("../config.json");
    DanfossWrapper dw(config.getAddrMapping());

    std::thread MQTT_MainThread(MQTT_WorkerThread, config.getMqttConfig());
    std::thread CAN_MainThread(CANBusWorkerThread, config.getCanbusConfig());
    std::this_thread::sleep_for(std::chrono::milliseconds (100));


    while (1) {
        if (!Common::CAN_receive_q.empty()) {
            // Retrieve CAN msg from CAN_receive_q
            CAN_Msg can_msg;
            can_msg = Common::CAN_receive_q.front();
            Common::CAN_receive_q.pop();

            // Convert CAN msg to MQTT msg
            MQTT_Msg mqtt_msg = dw.convertCAN2MQTT(can_msg);

            // Push MQTT msg into MQTT_publish_q
            Common::MQTT_publish_q.push(mqtt_msg);
        }

        if (!Common::MQTT_receive_q.empty()) {
            // Retrieve MQTT msg from MQTT_receive_q
            MQTT_Msg mqtt_msg = Common::MQTT_receive_q.front();
            Common::MQTT_receive_q.pop();

            // Convert MQTT msg to CAN msg
            CAN_Msg can_msg;
            can_msg = dw.convertMQTT2CAN(mqtt_msg);

            // Push CAN msg into CAN_publish_q
            Common::CAN_publish_q.push(can_msg);
        }
    }

    MQTT_MainThread.join();
    CAN_MainThread.join();
}
