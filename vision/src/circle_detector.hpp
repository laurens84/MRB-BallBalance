#ifndef CIRCLE_DETECTOR_HPP
#define CIRCLE_DETECTOR_HPP

#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>

class circle_detector {
  private:
    cv::VideoCapture cap;
    cv::Mat frame, gray;
    std::vector<cv::Vec3f> circles;

    std::vector<cv::Point> points;

  public:
    circle_detector(const uint8_t &deviceNum, const uint16_t &width, const uint16_t &height);

    void init();

    void detect_circles();

    const std::vector<cv::Point> &locate_circles();

    void display_circles(const std::string &window_name);
};

#endif // CIRCLE_DETECTOR_HPP