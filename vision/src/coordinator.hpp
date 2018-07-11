/**
 * @brief The coordinator file contains the Coordinator class used to communicate between the data received from the servo's and the
 * data from the circle detections.
 *
 * @file coordinator.hpp
 * @date 2018-07-11
 */
#ifndef COORDINATOR_HPP
#define COORDINATOR_HPP

#include "mrb_math.hpp"
#include "servo.hpp"

template <uint8_t NUM_SERVOS>
class Coordinator {
  private:
    std::array<Servo *, NUM_SERVOS> servos;

  public:
    /**
     * @brief Construct a new Coordinator object.
     *
     * @param servo_a The first servo.
     * @param servo_b The second servo.
     * @param servo_c The third servo.
     */
    Coordinator(Servo *servo_a, Servo *servo_b, Servo *servo_c) : servos{servo_a, servo_b, servo_c} {
    }

    /**
     * @brief Calculates the error for each servo using the set_point, ball position and scalar projection.
     *
     * @param set_point                         The position of the set_point.
     * @param ball_pos                          The position of the ball.
     * @return std::array<double, NUM_SERVOS>   Returns an array with error values for each servo.
     */
    std::array<double, NUM_SERVOS> calcError(const cv::Point &set_point, const cv::Point &ball_pos) {
        std::array<double, NUM_SERVOS> error;

        for (uint8_t i = 0; i < servos.size(); ++i) {
            error[i] = MRB_MATH::absolute(servos[i]->get_position() - set_point) -
                       MRB_MATH::scalar_proj(servos[i]->get_position() - set_point, servos[i]->get_position() - ball_pos);
        }

        //std::cout << '[' << error[0] << ", " << error[1] << ", " << error[2] << "]\n";

        return error;
    }

    /**
     * @brief Get the location of a servo by ID.
     *
     * @param id            The ID of a servo.
     * @return cv::Point*   Returns a pointer to the position of the servo.
     */
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