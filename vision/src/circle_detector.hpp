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

    std::array<cv::Point, 3> init(const cv::Size &blur_size, const int &min_radius, const int &max_radius);

    void detect_circles(const cv::Size &blur_size, const int &min_radius, const int &max_radius);

    const std::vector<cv::Point> &locate_circles();

    std::vector<cv::Vec3f> &getCircles();
    std::vector<cv::Point> &getCirclePoints();
    cv::Mat &getFrame();
};
#endif // CIRCLE_DETECTOR_HPP