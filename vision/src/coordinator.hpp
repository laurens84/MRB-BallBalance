#ifndef COORDINATOR_HPP
#define COORDINATOR_HPP

#include "circle_detector.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <memory>

struct Servo {};

class Coordinator {
  private:
    std::array<Servo &, 3> servos;

  public:
    Coordinator(Servo &servo_a, Servo &servo_b, Servo &servo_c) : servos{servo_a, servo_b, servo_c}, has_all_servos{false} {
    }
};

#endif // COORDINATOR_HPP