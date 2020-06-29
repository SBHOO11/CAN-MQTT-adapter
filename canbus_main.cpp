//
// Created by shibinhoo on 28/6/20.
//

#include <iostream>
#include <thread>
#include "CANUsb.h"
#include "Common.h"


using std::cout;
using std::cerr;
using std::endl;

void CAN_ReadTask(CANUsb& can);

void CANBusWorkerThread() {

    // Initialize CAN bus
    CANUsb can = CANUsb("vcan0");
    can.open();

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