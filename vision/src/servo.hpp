#ifndef SERVO_HPP
#define SERVO_HPP

#include "UART.hpp"
#include "opencv2/imgproc/imgproc.hpp"

class Servo {
  private:
    UART &serial;
    uint8_t id, motpos;
    cv::Point position;

  public:
    Servo(UART &serial, const uint8_t &id, const cv::Point &position);

    void write(uint8_t degees);

    void int_to_str(uint8_t num, char *buffer);

    uint8_t &get_motor_position();
    cv::Point &get_position();
    uint8_t &get_id();
};

#endif // SERVO_HPP