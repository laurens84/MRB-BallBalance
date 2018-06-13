#ifndef UART_H
#define UART_H

#include <errno.h> /* ERROR Number Definitions          */
#include <fcntl.h> /* File Control Definitions          */
#include <iostream>
#include <string>
#include <termios.h>/* POSIX Terminal Control Definitions*/
#include <unistd.h> /* UNIX Standard Definitions         */

class UART {
  private:
    char read_buffer[32];
    struct termios serial_port_settings;
    std::string device;
    int fd;

  public:
    UART(const std::string &device);

    int connect();

    void disconnect();

    void receive();

    int send(const char *write_buffer);
};

#endif