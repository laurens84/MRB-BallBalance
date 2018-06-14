#include "circle_detector.hpp"
#include <math.h>
#include <stdio.h>

Circle_detector::Circle_detector(const uint8_t &deviceNum, const uint16_t &width, const uint16_t &height) : cap(deviceNum) {
    if (cap.isOpened()) {
        cap.set(cv::CAP_PROP_FRAME_WIDTH, width);
        cap.set(cv::CAP_PROP_FRAME_HEIGHT, height);
    } else {
        std::cout << "No input device.\n";
    }
}

void Circle_detector::init(Coordinator &cod, const cv::Size &blur_size, const int &min_radius, const int &max_radius) {
    while (!cod.has_servos()) {
        cv::Point red, blue, green;

        cap >> frame;
        cv::Mat3b bgr_inv = ~frame;
        cv::Mat3b hsv_inv;
        cv::cvtColor(bgr_inv, hsv_inv, cv::COLOR_BGR2HSV); // Red
        cv::cvtColor(frame, frame, cv::COLOR_BGR2HSV);     // Blue & green.

        // Red
        inRange(hsv_inv, cv::Scalar(80, 70, 50), cv::Scalar(100, 255, 255), mask);
        cv::GaussianBlur(mask, mask, blur_size, 0);
        cv::HoughCircles(mask, circles, cv::HOUGH_GRADIENT, 1, mask.rows / 8, 100, 20, min_radius, max_radius);
        if (circles.size() > 0)
            red = cv::Point(cvRound(circles[0][0]), cvRound(circles[0][1]));

        // Blue
        circles.clear();
        inRange(frame, cv::Scalar(100, 120, 75), cv::Scalar(110, 255, 255), mask);
        cv::GaussianBlur(mask, mask, blur_size, 0);
        cv::HoughCircles(mask, circles, cv::HOUGH_GRADIENT, 1, mask.rows / 8, 100, 20, min_radius, max_radius);
        if (circles.size() > 0)
            blue = cv::Point(cvRound(circles[0][0]), cvRound(circles[0][1]));

        // Green
        circles.clear();
        inRange(frame, cv::Scalar(60, 120, 75), cv::Scalar(90, 255, 255), mask);
        cv::GaussianBlur(mask, mask, blur_size, 0);
        cv::HoughCircles(mask, circles, cv::HOUGH_GRADIENT, 1, mask.rows / 8, 100, 20, min_radius, max_radius);
        if (circles.size() > 0)
            green = cv::Point(cvRound(circles[0][0]), cvRound(circles[0][1]));

        if ((red.x != 0 && red.y != 0) && (blue.x != 0 && blue.y != 0) && (green.x != 0 && green.y != 0)) {
            double side_1 = sqrt(pow(red.x - blue.x, 2) + pow(red.y - blue.y, 2));
            double side_2 = sqrt(pow(red.x - green.x, 2) + pow(red.y - green.y, 2));
            double side_3 = sqrt(pow(blue.x - green.x, 2) + pow(blue.y - green.y, 2));
            double side_avg = (side_1 + side_2 + side_3) / 3;

            if ((side_1 - side_avg > -10) && (side_1 - side_avg < 10)) {
                // std::cout << "red: " << red << "\nblue: " << blue << "\ngreen: " << green << "\n\n";
                std::cout << "rb: " << side_1 << " rg: " << side_2 << " bg: " << side_3 << "\n";
                cod.setServos(std::unique_ptr<Servo>(new Servo('a', red)), std::unique_ptr<Servo>(new Servo('b', blue)),
                              std::unique_ptr<Servo>(new Servo('c', green)));
            }
        }
    }
}

void Circle_detector::detect_circles(const cv::Size &blur_size, const int &min_radius, const int &max_radius) {
    circles.clear();
    cap >> frame;
    cv::cvtColor(frame, gray, cv::COLOR_BGR2GRAY);
    cv::GaussianBlur(gray, gray, blur_size, 0);
    cv::HoughCircles(gray, circles, cv::HOUGH_GRADIENT, 1, gray.rows / 8, 100, 20, min_radius, max_radius);
}

const std::vector<cv::Point> &Circle_detector::locate_circles() {
    points.clear();

    if (circles.size() > 0) {
        for (uint8_t i = 0; i < circles.size(); i++) {
            cv::Point point = cv::Point(cvRound(circles[i][0]), cvRound(circles[i][1]));
            if ((point.x + point.y) > 0) {
                points.push_back(point);
            }
        }
    }

    return points;
}

std::vector<cv::Vec3f> &Circle_detector::getCircles() {
    return circles;
}

std::vector<cv::Point> &Circle_detector::getCirclePoints() {
    return points;
}

cv::Mat &Circle_detector::getFrame() {
    return frame;
}