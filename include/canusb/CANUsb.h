//
// Created by shibinhoo on 21/6/20.
//

#ifndef CAN_MQTT_ADAPTER_CAN_USB_H
#define CAN_MQTT_ADAPTER_CAN_USB_H

#include <linux/can.h>
#include <linux/can/raw.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <net/if.h>
#include <unistd.h>
#include <string>
#include <cstring>
#include <queue>

#include "CAN_common.h"

class CANUsb {
public:
    CANUsb(std::string ITF_name): ITF_name_(ITF_name) {} ;
    int open();
    int write(CAN_Msg& can_msg);
    int read(CAN_Msg& can_msg);
    int close();
private:
    const std::string ITF_name_;
    int socket_fd_{0};
    can_frame write_can_frame_;
    can_frame read_can_frame_;
};


#endif //CAN_MQTT_ADAPTER_CAN_USB_H
