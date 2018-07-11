/**
 * @brief This class is used to connect the Arduino with the PC.
 *
 * @file UART.hpp
 * @date 2018-07-11
 */
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
    /**
     * @brief Construct a new UART object.
     *
     * @param device The path to the device / COM port.
     */
    UART(const std::string &device);

    /**
     * @brief Connect to the device.
     *
     * @return true   If connection was successful.
     * @return false  If connection failed.
     */
    bool connect();

    /**
     * @brief Disconnects from the device.
     *
     */
    void disconnect();

    /**
     * @brief Sends data to the device.
     *
     * @param write_buffer  The data to be transferred.
     * @return int          Returns whether the transfer was successful or not.
     */
    int send(const char *write_buffer);

    /**
     * @brief Destroy the UART object after closing the connection.
     *
     */
    ~UART();
};

#endif
