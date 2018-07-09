#ifndef COORDINATOR_HPP
#define COORDINATOR_HPP

#include "mrb_math.hpp"
#include "servo.hpp"

template <uint8_t NUM_SERVOS>
class Coordinator {
  private:
    std::array<Servo*, NUM_SERVOS> servos;

  public:
    Coordinator(Servo *servo_a, Servo *servo_b, Servo *servo_c) : servos{servo_a, servo_b, servo_c} {
    }

    std::array<double, NUM_SERVOS> calcError(const cv::Point &set_point, const cv::Point &ball_pos) {
        std::array<double, NUM_SERVOS> error;

        for (uint8_t i = 0; i < servos.size(); ++i) {
            error[i] = MRB_MATH::absolute(servos[i]->get_position() - set_point) - MRB_MATH::scalar_proj(servos[i]->get_position() - set_point, servos[i]->get_position() - ball_pos);
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