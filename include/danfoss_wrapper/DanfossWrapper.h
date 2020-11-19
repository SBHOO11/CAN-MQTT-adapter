//
// Created by shibinhoo on 22/6/20.
//

#ifndef CAN_MQTT_ADAPTER_DANFOSSWRAPPER_H
#define CAN_MQTT_ADAPTER_DANFOSSWRAPPER_H

#include <iostream>
#include <string>
#include <map>
#include <algorithm>
#include "json/json.h"
#include "Common.h"
#include "CAN_common.h"
#include "mqtt_common.h"

class DanfossWrapper {
public:
    DanfossWrapper(Json::Value map_) : addr_map_(map_) {};
    MQTT_Msg convertCAN2MQTT(CAN_Msg &can_data);
    CAN_Msg convertMQTT2CAN(MQTT_Msg &mqtt_msg);

private:
    Json::Value addr_map_;
};


#endif //CAN_MQTT_ADAPTER_DANFOSSWRAPPER_H
