//
// Created by shibinhoo on 27/6/20.
//

#include <iostream>
#include <thread>
#include <chrono>
#include "Common.h"
#include "CAN_common.h"

using std::cout;
using std::endl;


void MQTT_WorkerThread();
void CANBusWorkerThread();

int main(int argc, char** argv) {
    std::thread MQTT_MainThread(MQTT_WorkerThread);
    std::thread CAN_MainThread(CANBusWorkerThread);
    std::this_thread::sleep_for(std::chrono::milliseconds (100));

    // MQTT testing below
//    cout << ">> ";
//    std::string msg;
//    while (std::getline(std::cin, msg)) {
//        Common::MQTT_publish_q.push(msg);
//        cout << ">> " << endl;
//    }

    // CAN testing below
    CANData can_data;
    can_data.can_id = 5;
    can_data.data = {1,2,3,4};
    while (1) {
        Common::CAN_publish_q.push(can_data);
        std::this_thread::sleep_for(std::chrono::milliseconds (50));
        can_data.can_id += 1;

        if (!Common::CAN_receive_q.empty()) {
            CANData can_data;
            can_data = Common::CAN_receive_q.front();
            Common::CAN_receive_q.pop();

            // TODO: Danfoss Wrapper (conversion)
//            std::string msg{};
//            msg = Danfoss...(can_data)

            // Push converted msg into MQTT_publish_q
//            Common::MQTT_publish_q.push(msg);

            cout << "CAN received - " << can_data.can_id << "#";
            for (const auto &value : can_data.data) {
                cout << value << ".";
            }
            cout << endl;
        }
    }

    // Normal Loop
//    while (1) {
//        if (!Common::CAN_receive_q.empty()) {
//            CANData can_data;
//            can_data = Common::CAN_receive_q.front();
//            Common::CAN_receive_q.pop();
//
//            // TODO: Danfoss Wrapper (conversion)
////            std::string msg{};
////            msg = Danfoss...(can_data)
//
//            // Push converted msg into MQTT_publish_q
////            Common::MQTT_publish_q.push(msg);
//        }
//
//        if (!Common::MQTT_receive_q.empty()) {
//            std::string msg{};
//            msg = Common::MQTT_receive_q.front();
//            Common::MQTT_receive_q.pop();
//
//            // TODO: Danfoss Wrapper (conversion)
////            CANData can_data;
////            can_data = Danfoss.....(msg);
//
//            // Push converted CANData into CAN_publish_q
////            Common::CAN_publish_q.push(can_data);
//        }
//    }

    MQTT_MainThread.join();
    CAN_MainThread.join();
}
