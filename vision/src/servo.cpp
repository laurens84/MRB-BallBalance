#include "servo.hpp"

Servo::Servo(UART &serial, const uint8_t &id, const cv::Point &position) : serial{serial}, id{id}, position{position} {
}

void Servo::write(uint8_t degrees) {
    motpos = degrees;

    char data[5];
    data[0] = id;

    this->int_to_str(degrees, data);

    data[4] = 'n';
    serial.send(data);
}

void Servo::int_to_str(uint8_t num, char *buffer) {
    for (uint8_t i = 3; 0 < i; --i) {
        *(buffer + i) = (num % 10) + 48;
        num /= 10;
    }
}

uint8_t &Servo::get_motor_position() {
    return motpos;
}

cv::Point &Servo::get_position() {
    return position;
}

uint8_t &Servo::get_id() {
    return id;
}