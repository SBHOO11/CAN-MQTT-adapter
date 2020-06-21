//
// Created by shibinhoo on 22/6/20.
//

#ifndef CAN_MQTT_ADAPTER_DANFOSSWRAPPER_H
#define CAN_MQTT_ADAPTER_DANFOSSWRAPPER_H

#include <CAN_common.h>

class DanfossWrapper {
public:
    static bool parseCANMsg(const CANData& can_msg);

    // Node ID for respective commands
    static const int kCAN_joystick_id  {10} ;
};


#endif //CAN_MQTT_ADAPTER_DANFOSSWRAPPER_H
