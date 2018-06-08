#ifndef COORDINATOR_HPP
#define COORDINATOR_HPP

#include "circle_detector.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>

class Coordinator {
  private:
    bool has_servos;
    Servo *servos[3];

  public:
    Coordinator() : has_servos{false} {
    }

    ~Coordinator() {
        delete[] servos;
    }

    void setServos(Servo *servo_a, Servo *servo_b, Servo *servo_c);

    bool get_has_servos() {
        return has_servos;
    };
};

#endif // COORDINATOR_HPP