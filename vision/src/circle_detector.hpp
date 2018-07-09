#ifndef CIRCLE_DETECTOR_HPP
#define CIRCLE_DETECTOR_HPP

#include <math.h>
#include <stdio.h>
#include <unistd.h>
#include "mrb_math.hpp"
#include <iostream>

class MRB_controller;

class Circle_detector {
  private:
    MRB_controller * MRB_ctrl;
    cv::Mat gray, mask;

    std::vector<cv::Vec3f> circles;
    std::vector<cv::Point> points;

  public:
    Circle_detector(MRB_controller *MRB_ctrl);

    std::vector<cv::Point> init(const cv::Size &blur_size, const int &min_radius, const int &max_radius);

    void detect_circles(const cv::Size &blur_size, const int &min_radius, const int &max_radius);

    const std::vector<cv::Point> &locate_circles();

    std::vector<cv::Vec3f> &get_circles();
    std::vector<cv::Point> &get_circle_points();
};

#endif // CIRCLE_DETECTOR_HPP
