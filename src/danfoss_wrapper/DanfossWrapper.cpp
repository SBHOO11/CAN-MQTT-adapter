//
// Created by shibinhoo on 22/6/20.
//

#include <iostream>
#include "DanfossWrapper.h"

bool DanfossWrapper::parseCANMsg(const CANData &can_msg) {
    if (can_msg.can_id == kCAN_joystick_id) {
        uint16_t js_x;
        ENCODE_2BYTES_TO_NUM16(can_msg.data[0], can_msg.data[1], js_x);

        uint16_t js_y;
        ENCODE_2BYTES_TO_NUM16(can_msg.data[2], can_msg.data[3], js_y);

        std::cout << "Received cmd from Joystick, x: [" << js_x
                  << "]  y: [" << js_y << "]" << std::endl;
    }
}
