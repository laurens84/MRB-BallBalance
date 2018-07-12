#include "UART.hpp"

UART::UART(const std::string &device) : device{device} {
    tcgetattr(fd, &serial_port_settings);

    cfsetispeed(&serial_port_settings, B115200);   /* Set Read  Speed as 115200                       */
    cfsetospeed(&serial_port_settings, B115200);   /* Set Write Speed as 115200                       */
    tcsetattr(fd, TCSANOW, &serial_port_settings); // Set all atrributes.
}

bool UART::connect() {
    fd = open(device.c_str(), O_RDWR | O_NOCTTY);
    sleep(3);
    if (fd == -1) {
        std::cout << "UART connection failed.\n";
        return 0; // Connect failed.
    }

    else {
        std::cout << "UART connection success.\n";
        return 1; // Connect successfull.
    }
}

void UART::disconnect() {
    close(fd);
}

int UART::send(const char *write_buffer) {
    return write(fd, write_buffer, sizeof(write_buffer));
}

UART::~UART() {
    close(fd);
}
