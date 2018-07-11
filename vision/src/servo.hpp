/**
 * @brief This class is used to control a servo.
 *
 * @file servo.hpp
 * @date 2018-07-11
 */
#ifndef SERVO_HPP
#define SERVO_HPP

#include "UART.hpp"
#include "opencv2/imgproc/imgproc.hpp"

class Servo {
  private:
    UART &serial;
    uint8_t id, angle;
    cv::Point position;

  public:
    /**
     * @brief Construct a new Servo object.
     *
     * @param serial    The UART object.
     * @param id        The servo ID.
     * @param position  The servo position.
     */
    Servo(UART &serial, const uint8_t &id, const cv::Point &position);

    /**
     * @brief Changes the servo angle based on a certain value.
     *
     * @param degees The value used to change the servo angle.
     */
    void write(const uint8_t &degees);

    /**
     * @brief Converts an integer to a string.
     *
     * @param num     The integer to be converted.
     * @param buffer  The output string.
     */
    void int_to_str(uint8_t num, char *buffer);

    /**
     * @brief Get the servo angle.
     *
     * @return uint8_t& The motor angle.
     */
    uint8_t &get_motor_angle();

    /**
     * @brief Get the servo position.
     *
     * @return cv::Point& The servo position.
     */
    cv::Point &get_position();

    /**
     * @brief Get the servo id.
     *
     * @return uint8_t& The servo id.
     */
    uint8_t &get_id();
};

#endif // SERVO_HPP
