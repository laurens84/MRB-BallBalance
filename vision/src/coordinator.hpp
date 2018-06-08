#ifndef COORDINATOR_HPP
#define COORDINATOR_HPP

#include "circle_detector.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <memory>

struct Servo;

class Coordinator {
  private:
    bool has_servos;
    std::array<std::unique_ptr<Servo>, 3> servos;

  public:
    Coordinator() : has_servos{false} {
    }

    void setServos(std::unique_ptr<Servo> servo_a, std::unique_ptr<Servo> servo_b, std::unique_ptr<Servo> servo_c);

    bool get_has_servos() {
        return has_servos;
    };
};

#endif // COORDINATOR_HPP