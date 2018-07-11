/**
 * @brief This file contains the circle_detector class used to detect circles and their locations in a given frame.
 *
 * @file circle_detector.hpp
 * @date 2018-07-11
 */

#ifndef CIRCLE_DETECTOR_HPP
#define CIRCLE_DETECTOR_HPP

#include "mrb_math.hpp"
#include <iostream>
#include <math.h>
#include <stdio.h>
#include <unistd.h>

class MRB_controller;

class Circle_detector {
  private:
    MRB_controller *MRB_ctrl;
    cv::Mat gray, mask;

    std::vector<cv::Vec3f> circles;
    std::vector<cv::Point> points;

  public:
    /**
     * @brief Construct a new Circle_detector object.
     *
     * @param MRB_ctrl A pointer to the MRB_controller which contains the frame and other important methods.
     */
    Circle_detector(MRB_controller *MRB_ctrl);

    /**
     * @brief This class is used to detect the servo positions.
     * This is done by detecting the colored circles on the servo's and storing their locations.
     * The method continues till it has found the three circles and the three circles are in valid locations.
     *
     * @param blur_size                 The size of the Gaussian kernel.
     * @param min_radius                The minimum size of the circle.
     * @param max_radius                The maximum size of the circle.
     * @return std::vector<cv::Point>   A vector filled with the positions of detected circles.
     */
    std::vector<cv::Point> init(const cv::Size &blur_size, const int &min_radius, const int &max_radius);

    /**
     * @brief This method detects circles in the current frame received from the MRB_controller and stores them in a vector.
     *
     * @param blur_size   The size of the Gaussian kernel.
     * @param min_radius  The minimum size of the circle.
     * @param max_radius  The maximum size of the circle.
     */
    void detect_circles(const cv::Size &blur_size, const int &min_radius, const int &max_radius);

    /**
     * @brief This method returns the location of the circles stored in a vector.
     *
     * @return const std::vector<cv::Point>& A vector filled with the locations of the circles stored in the circles vector.
     */
    const std::vector<cv::Point> &locate_circles();

    /**
     * @brief Get the circles.
     *
     * @return std::vector<cv::Vec3f>&  A vector of circles.
     */
    std::vector<cv::Vec3f> &get_circles();

    /**
     * @brief Get the circle locations.
     *
     * @return std::vector<cv::Point>& A vector filled with the locations of the circles stored in the circles vector.
     */
    std::vector<cv::Point> &get_circle_points();
};

#endif // CIRCLE_DETECTOR_HPP
