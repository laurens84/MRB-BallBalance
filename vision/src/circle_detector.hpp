#ifndef CIRCLE_DETECTOR_HPP
#define CIRCLE_DETECTOR_HPP

#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>

class Circle_detector {
  private:
    cv::VideoCapture cap;
    cv::Mat frame, gray;
    std::vector<cv::Vec3f> circles;

    std::vector<cv::Point> points;

    cv::Mat mask;

    bool triangle_detected;

  public:
    Circle_detector(const uint8_t &deviceNum, const uint16_t &width, const uint16_t &height);

    std::vector<cv::Point> init(const cv::Size &blur_size, const int &min_radius, const int &max_radius);

    void detect_circles(const cv::Size &blur_size, const int &min_radius, const int &max_radius);

    const std::vector<cv::Point> &locate_circles();

    std::vector<cv::Vec3f> &get_circles();
    std::vector<cv::Point> &get_circle_points();
    cv::Mat &get_frame();
};
#endif // CIRCLE_DETECTOR_HPP