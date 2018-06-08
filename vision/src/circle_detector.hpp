#ifndef CIRCLE_DETECTOR_HPP
#define CIRCLE_DETECTOR_HPP

#include "coordinator.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <memory>

class Coordinator;

struct Servo {
    uint8_t color_code;
    cv::Point position;

    Servo(const uint8_t &cc, const cv::Point &pos) : color_code{cc}, position{pos} {
    }
};

class Circle_detector {
  private:
    cv::VideoCapture cap;
    cv::Mat frame, gray;
    std::vector<cv::Vec3f> circles;

    std::vector<cv::Point> points;

    cv::Mat mask;

  public:
    Circle_detector(const uint8_t &deviceNum, const uint16_t &width, const uint16_t &height);

    void init(Coordinator &cod, const cv::Size &blur_size, const int &min_radius, const int &max_radius);

    void detect_circles(const cv::Size &blur_size, const int &min_radius, const int &max_radius);

    const std::vector<cv::Point> &locate_circles();

    void display_circles(const std::string &window_name);
};

#endif // CIRCLE_DETECTOR_HPP