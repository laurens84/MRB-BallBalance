/**
 * @brief The MRB controller handles the window object and provides window data that other objects can use.
 *
 * @file mrb.hpp
 * @date 2018-07-11
 */

#ifndef MRB_HPP
#define MRB_HPP

#include "circle_detector.hpp"
#include "mrb_math.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "pid.hpp"
#include <iostream>

class MRB_controller {
  private:
    std::string window_name;
    cv::VideoCapture cap;
    cv::Mat frame;

    cv::Point set_point;

    bool triangle_detected;

    std::vector<PID *> PID_ctrls;

    /**
     * @brief
     *
     * @param evt   The fired event.
     * @param x     The x position of the click.
     * @param y     The y position of the click.
     * @param flags ...
     * @param param The paramater the new position will be stored in.
     */
    static void mouse_handler(int evt, int x, int y, int flags, void *param);

  public:
    /**
     * @brief Construct a new mrb controller object.
     *
     * @param window_name The name of the to be created window.
     * @param deviceNum   The device number of the camera.
     * @param width       The width of the capture.
     * @param height      The height of the capture.
     */
    MRB_controller(const std::string &window_name, const uint8_t &deviceNum, const uint16_t &width, const uint16_t &height);

    /**
     * @brief
     *
     * @param circles         The detected circles.
     * @param servo_positions The position of the servo's.
     * @return true           Returns true if the initialization has been successful.
     * @return false          Returns false if the initialization failed.
     */
    bool init(Circle_detector &circles, std::vector<cv::Point> &servo_positions);

    /**
     * @brief This method displays a star on the window at the position of the circles.
     *
     * @param points A vector of points which contain the position of a detected circle.
     */
    void display_circles(std::vector<cv::Point> &points) const;

    /**
     * @brief Store pointers to the pid controllers in a vector.
     *
     * @param pid_controllers A vector with the PID controllers.
     */
    void set_pid_controllers(std::vector<PID> &pid_controllers);

    /**
     * @brief Displays the position of the set_point on the window.
     *
     */
    void display_set_point();

    /**
     * @brief Set the new set_point value.
     *
     * @param mouse_pos The new position.
     */
    void new_set_point(const cv::Point &new_pos);

    /**
     * @brief Stores a new image from the VideoCapture into the frame matrix.
     *
     */
    void renew_frame();

    /**
     * @brief Get the frame object.
     *
     * @return cv::Mat& The current frame.
     */
    cv::Mat &get_frame();

    /**
     * @brief Get the cap object.
     *
     * @return cv::VideoCapture& A reference to the VideoCapture object.
     */
    cv::VideoCapture &get_cap();

    /**
     * @brief Get the window name.
     *
     * @return std::string& The window name.
     */
    std::string &get_window_name();

    /**
     * @brief Get the mouse position.
     *
     * @return cv::Point& The mouse_position.
     */
    cv::Point &get_mouse_pos();

    /**
     * @brief Get the mouse position if it differs from the current mouse position.
     *
     * @return cv::Point& The mouse_position.
     */
    cv::Point &get_mouse_pos_on_click();

    /**
     * @brief Get the triangle detected boolean object.
     *
     * @return bool& The triangle_detected value.
     */
    bool &get_triangle_detected();
};

#endif // MRB_HPP
