#ifndef SERVO_HPP
#define SERVO_HPP
#include "UART.hpp"
#include "opencv2/imgproc/imgproc.hpp"

class servo {
  private:
    UART &serial;
    uint8_t id;
    cv::Point position;

  public:
    servo(UART &serial, const uint8_t &id, const cv::Point &position);

    void write(uint8_t degees);

    void int_to_str(uint8_t num, char *buffer);
};

#endif