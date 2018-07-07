#ifndef COORDINATOR_HPP
#define COORDINATOR_HPP

#include "circle_detector.hpp"
#include "servo.hpp"

template <uint8_t NUM_SERVOS>
class Coordinator {
  private:
    std::array<Servo *, NUM_SERVOS> servos;

  public:
    Coordinator(Servo *servo_a, Servo *servo_b, Servo *servo_c) : servos{servo_a, servo_b, servo_c} {
    }

    // double get_length_diff(const cv::Point &a, const cv::Point &b) {
    //    return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2));
    //}

    double dot(const Point &a, const Point &b) {
        return (a.x * b.x) + (a.y * b.y);
    }

    double absolute(const Point &a) {
        return sqrt(pow(a.x, 2) + pow(a.y, 2));
    }

    double scalar_proj() {
        return dot(p2, p1) / absolute(p1);
    }

    std::array<double, NUM_SERVOS> calcError(const cv::Point &set_point, const cv::Point &ball_pos) {
        std::array<double, NUM_SERVOS> error;

        for (uint8_t i = 0; i < servos.size(); ++i) {
            // error[i] = get_length_diff(servos[i]->get_position(), set_point) - get_length_diff(servos[i]->get_position(),
            // ball_pos); error[i] *= -1; error[i] = absolute()
        }

        return error;
    }

    cv::Point *get_servo_location(const uint8_t &id) {
        for (uint8_t i = 0; i < servos.size(); ++i) {
            if (servos[i]->get_id() == id) {
                return &servos[i]->get_position();
            }
        }

        return nullptr;
    }
};

#endif // COORDINATOR_HPP