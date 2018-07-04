#include "UART.hpp"

UART::UART(const std::string &device) : device{device} {
    tcgetattr(fd, &serial_port_settings);

    cfsetispeed(&serial_port_settings, B115200);   /* Set Read  Speed as 115200                       */
    cfsetospeed(&serial_port_settings, B115200);   /* Set Write Speed as 115200                       */
    tcsetattr(fd, TCSANOW, &serial_port_settings); // Set all atrributes.
}

int UART::connect() {
    fd = open(device.c_str(), O_RDWR | O_NOCTTY);
    if (fd == -1) {
        std::cout << "UART connection failed.\n";
        return -1; // Connect failed.
    }

    else {
        std::cout << "UART connection success.\n";
        return 1; // Connect successfull.
    }
}

void UART::disconnect() {
    close(fd);
}

void UART::receive() {
    tcflush(fd, TCIFLUSH);
    int bytes_read = 0;
    bytes_read = read(fd, &read_buffer, 32);

    for (int i = 0; i < bytes_read; i++)
        printf("%c", read_buffer[i]);
}

int UART::send(const char *write_buffer) {
    // std::cout << write_buffer << '\n';
    return write(fd, write_buffer, sizeof(write_buffer));
}