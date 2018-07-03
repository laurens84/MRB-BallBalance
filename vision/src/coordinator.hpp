#ifndef COORDINATOR_HPP
#define COORDINATOR_HPP

#include "circle_detector.hpp"
#include "servo.hpp"

class Coordinator {
  private:
    std::array<Servo *, 3> servos;

  public:
    Coordinator(Servo *servo_a, Servo *servo_b, Servo *servo_c) : servos{servo_a, servo_b, servo_c} {
    }

    cv::Point *get_servo_location(const uint8_t &id);
};

#endif // COORDINATOR_HPP