//
// Created by shibinhoo on 28/6/20.
//

#include <iostream>
#include <thread>
#include "json/json.h"
#include "CANUsb.h"
#include "Common.h"


using std::cout;
using std::cerr;
using std::endl;

void CAN_ReadTask(CANUsb& can);

void CANBusWorkerThread(Json::Value config) {

    // Initialize CAN bus
    std::string socket_name = config["socket_name"].asString();
    std::cout << "Initializing CANBus socket (" << socket_name << ")" << std::endl;
    CANUsb can = CANUsb(socket_name);
    can.open();
    std::cout << "[OK] CANBus socket (" << socket_name << ")" << std::endl;

    std::thread CAN_ReadThread(CAN_ReadTask, std::ref(can));

    while (1) {
        if (!Common::CAN_publish_q.empty()) {
            CAN_Msg can_msg;
            can_msg = Common::CAN_publish_q.front();
            Common::CAN_publish_q.pop();
            can.write(can_msg);
        }
    }

    CAN_ReadThread.join();
}

void CAN_ReadTask(CANUsb& can) {

    while (1) {
        CAN_Msg can_msg;
        can.read(can_msg);
        Common::CAN_receive_q.push(can_msg);
    }
}