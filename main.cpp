//
// Created by shibinhoo on 27/6/20.
//

#include <iostream>
#include <thread>
#include <chrono>
#include "Common.h"

using std::cout;
using std::endl;


void MQTT_WorkerThread();
void CANBusWorkerThread();

int main(int argc, char** argv) {
    std::thread MQTT_MainThread(MQTT_WorkerThread);
    std::thread CAN_MainThread(CANBusWorkerThread);
    std::this_thread::sleep_for(std::chrono::milliseconds (100));

    cout << ">> ";
    std::string msg;
    while (std::getline(std::cin, msg)) {
        Common::MQTT_publish_q.push(msg);
        cout << ">> " << endl;
    }

    MQTT_MainThread.join();
    CAN_MainThread.join();
}
