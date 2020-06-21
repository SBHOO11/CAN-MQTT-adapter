//
// Created by shibinhoo on 21/6/20.
//

#ifndef CAN_MQTT_ADAPTER_CAN_COMMON_H
#define CAN_MQTT_ADAPTER_CAN_COMMON_H

#include <array>

#define CAN_PAYLOAD_LENGTH 8
#define LITTLE_ENDIAN_ENABLE 1    // 0 means big endian


// Encode-decode macros
#if (LITTLE_ENDIAN_ENABLE == 1)
    #define ENCODE_2BYTES_TO_NUM16(b1, b2, dst) ( (dst) = ( (b2) << 8) | (b1))
	#define ENCODE_4BYTES_TO_NUM32(b1, b2, b3, b4, dst) ( (dst) =  ((b4) << 24) | ( (b3) << 16) | ( (b2) << 8) | (b1))
	#define DECODE_NUM16_TO_2BYTES(src, b1, b2)  ( ( (b2) = (src) >> 8 ), ( (b1) = (src) & 0x00ff ) )
	#define DECODE_NUM32_TO_4BYTES(src, b1, b2, b3, b4)  ( ( (b4) = (src) >> 24 ), ( (b3) = (src) >> 16 ), ( (b2) = (src) >> 8 ), ( (b1) = (src) & 0x000000ff ) )
#else
    #define ENCODE_2BYTES_TO_NUM16(b1, b2, dst) ( (dst) = ((b1) << 8) | (b2))
    #define ENCODE_4BYTES_TO_NUM32(b1, b2, b3, b4, dst) ( (dst) =  ((b1) << 24) | ((b2) << 16) | ( (b3) << 8) | (b4) )
    #define DECODE_NUM16_TO_2BYTES(src, b1, b2)  ( ( (b1) = (src) >> 8 ), ( (b2) = (src) & 0x00ff ) )
    #define DECODE_NUM32_TO_4BYTES(src, b1, b2, b3, b4)  ( ( (b1) = (src) >> 24 ), ( (b2) = (src) >> 16 ), ( (b3) = (src) >> 8 ), ( (b4) = (src) & 0x000000ff ) )
#endif
#endif //CAN_MQTT_ADAPTER_CAN_COMMON_H

class CANData {
public:
    uint can_id;
    std::array<uint, 8> data;
};
