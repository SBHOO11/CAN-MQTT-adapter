//
// Created by shibinhoo on 21/6/20.
//

#include <iostream>
#include "CANUsb.h"

int CANUsb::open() {

    std::cout << "Initialize CANusb interface " << ITF_name_ << std::endl;

    socket_fd_ = socket(PF_CAN, SOCK_RAW, CAN_RAW);
    if (socket_fd_ < 0) {
        std::cerr << "Could not open CANBus socket" << std::endl;
        return -1;
    }

    std::cout << "CANBus socket opened successfully" << std::endl;

    std::cout << "Getting network interface index" << std::endl;
    struct sockaddr_can addr{};
    struct ifreq ifr{};
    strcpy(ifr.ifr_name, ITF_name_.c_str());
    if (ioctl(socket_fd_, SIOCGIFINDEX, &ifr) < 0) {
        std::cerr << "Error setting device parameters (ioctl)" << std::endl;
        return -1;
    }

    std::cout << "Binding CAN socket" << std::endl;
    addr.can_family = AF_CAN;
    addr.can_ifindex = ifr.ifr_ifindex;
    if (bind(socket_fd_, (struct sockaddr*)(&addr), sizeof(addr))) {
        std::cerr << "Error binding CAN interface" << std::endl;
        return -1;
    }

    write_can_frame_.can_dlc = CAN_PAYLOAD_LENGTH;
    read_can_frame_.can_dlc = CAN_PAYLOAD_LENGTH;

    std::cout << "CANBus initialization complete, socket fd: " << socket_fd_ << std::endl;
    return socket_fd_;
}

int CANUsb::close() {
    int ret = ::close(socket_fd_);
    if (ret == 0) {
        std::cout << "Successfully closed socket" << std::endl;
    }
    return ::close(socket_fd_);
}

int CANUsb::write(CANData& can_data) {

    write_can_frame_.can_id = can_data.can_id;
    std::copy( std::begin(can_data.data),
               std::end(can_data.data),
               std::begin(write_can_frame_.data));

    return ::write(socket_fd_, &write_can_frame_, sizeof(write_can_frame_));
}

int CANUsb::read(CANData& can_data) {

    int ret = ::read(socket_fd_, &read_can_frame_, sizeof(struct can_frame));

    if (ret > 0) {
        can_data.can_id = read_can_frame_.can_id;
        std::copy(std::begin(read_can_frame_.data), std::end(read_can_frame_.data), std::begin(can_data.data));
    }

    return ret;
}