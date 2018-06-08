#include "UART.hpp"

UART::UART(const std::string &device) : device{device} {
    tcgetattr(fd, &serial_port_settings);
}

void UART::connect() {
    fd = open(device.c_str(), O_RDWR | O_NOCTTY);
    if (fd == -1)
        std::cout << "\n  Error! in Opening ttyUSB0\n";
    else
        std::cout << "\n  ttyUSB0 Opened Successfully\n";
}

void UART::disconnect() {
    close(fd);
}

void UART::set_baud(const speed_t &baud) {
    cfsetispeed(&serial_port_settings, baud);
    cfsetospeed(&serial_port_settings, baud);
}

void UART::receive() {
    tcflush(fd, TCIFLUSH);
    int bytes_read = 0;
    bytes_read = read(fd, &read_buffer, 32);

    for (int i = 0; i < bytes_read; i++)
        printf("%c", read_buffer[i]);
}

int UART::send() {
    char write_buffer[] = "A90"; /* Buffer containing characters to write into port	     */
    int bytes_written = 0;       /* Value for storing the number of bytes written to the port */

    return bytes_written = write(fd, write_buffer, sizeof(write_buffer));
}