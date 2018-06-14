#include "servo.hpp"

servo::servo(UART &serial, const uint8_t &id, const cv::Point &position) : serial{serial}, id{id}, position{position} {
}

void servo::write(uint8_t degrees) {
    char data[4];
    data[0] = id;

    this->int_to_str(degrees, data);

    serial.send(data);
    motpos = degrees;
}

void servo::int_to_str(uint8_t num, char *buffer) {
    for (uint8_t i = 3; 0 < i; --i) {
        *(buffer + i) = (num % 10) + 48;
        num /= 10;
    }
}

uint8_t &servo::get_motor_position() {
    return motpos;
}