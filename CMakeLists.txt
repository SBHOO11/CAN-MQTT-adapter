cmake_minimum_required(VERSION 3.16)
project(CAN_MQTT_adapter)

set(CMAKE_CXX_STANDARD 14)

include_directories(
        include/canusb
        include/danfoss_wrapper
        include/mqtt
        include/common
        )

add_executable(CAN_MQTT_adapter
        main.cpp
        mqtt_main.cpp
        src/mqtt/mqtt.cpp
        src/common/Common.cpp
        canbus_main.cpp
        src/canusb/CANUsb.cpp
        src/danfoss_wrapper/DanfossWrapper.cpp
        )


find_library(PAHO_MQTT_C_LIB paho-mqtt3as)
find_library(PAHO_MQTT_CPP_LIB paho-mqttpp3)
find_library(THREAD_LIB pthread)

target_link_libraries(CAN_MQTT_adapter ${PAHO_MQTT_CPP_LIB} ${PAHO_MQTT_C_LIB} ${THREAD_LIB})

