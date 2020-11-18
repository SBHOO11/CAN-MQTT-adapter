//
// Created by shibinhoo on 22/6/20.
//

#ifndef CAN_MQTT_ADAPTER_DANFOSSWRAPPER_H
#define CAN_MQTT_ADAPTER_DANFOSSWRAPPER_H

#include <string>
#include <map>
#include <algorithm>
#include "Common.h"
#include "CAN_common.h"
#include "mqtt_common.h"

class DanfossWrapper {
public:
    static MQTT_Msg convertCAN2MQTT(CAN_Msg &can_data);
    static CAN_Msg convertMQTT2CAN(MQTT_Msg &mqtt_msg);

private:
    static std::map<uint, std::string> CAN_id_2_MQTT_header_map_;
};


#endif //CAN_MQTT_ADAPTER_DANFOSSWRAPPER_H
