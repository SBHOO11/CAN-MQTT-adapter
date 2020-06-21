#include <iostream>
#include <iomanip>
#include <CANUsb.h>

int main(int argc, char** argv) {
    std::cout << "Hello World" << std::endl;

    CANUsb obj = CANUsb("canusb");
    obj.open();

    CANData can_data;

//    while (true) {
//        obj.read(&can_data);
//
//        std::cout << "[ID] " << std::hex << can_data.can_id << " - ";
//        for (const auto &value : can_data.data) {
//            std::cout << value << " ";
//        }
//        std::cout << std::endl;
//    }

    can_data.can_id = 15;
    can_data.data = {1,2,3,4,5,6,7,8};
    obj.write(can_data);

    obj.close();

    return 0;
}