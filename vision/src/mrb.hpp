#ifndef MRB_HPP
#define MRB_HPP

#include <iostream>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "mrb_math.hpp"
#include "circle_detector.hpp"

class MRB_controller {
private:
    std::string window_name;
    cv::VideoCapture cap;
    cv::Mat frame;

    cv::Point set_point;

    bool triangle_detected;

    static void mouse_handler(int evt, int x, int y, int flags, void *param);

public:
    MRB_controller(const std::string & window_name, const uint8_t &deviceNum, const uint16_t &width, const uint16_t &height);

    bool init(Circle_detector &circles, std::vector<cv::Point> &servo_positions);

    void display_circles(std::vector<cv::Point> &points) const; // Maybe belongs in circle_detector.

    void set_mouse_pos(const cv::Point &mouse_pos);

    void renew_frame();

    cv::Mat & get_frame();
    cv::VideoCapture & get_cap();
    std::string &get_window_name();
    cv::Point &get_mouse_pos();
    cv::Point &get_mouse_pos_on_click();
    bool &get_triangle_detected();
};

#endif // MRB_HPP
