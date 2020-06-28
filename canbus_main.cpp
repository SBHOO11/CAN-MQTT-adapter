//
// Created by shibinhoo on 28/6/20.
//

#include <iostream>
#include <thread>
#include "CANUsb.h"


using std::cout;
using std::cerr;
using std::endl;

void CAN_ReadTask(CANUsb& can);

void CANBusWorkerThread() {

    // Initialize CAN bus
    CANUsb can = CANUsb("vcan0");
    can.open();

    std::thread CAN_ReadThread(CAN_ReadTask, std::ref(can));

//    while (1) {
//        // Check CAN_publish_q, if msg is ready
//            // if yes, publish CAN msg
//
//        // Check internal_recv_q, if msg is ready
//            // if yes, pass the CAN msg to CAN_receive_q
//    }

    CAN_ReadThread.join();
}

void CAN_ReadTask(CANUsb& can) {

    while (1) {
        CANData can_data;
        can.read(can_data);
        cout << "CAN received - " << can_data.can_id << "#";
        for (const auto &value : can_data.data) {
            cout << value << ".";
        }
        cout << endl;
    }
}