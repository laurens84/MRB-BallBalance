#include "circle_detector.hpp"

circle_detector::circle_detector(const uint8_t &deviceNum, const uint16_t &width, const uint16_t &height) : cap(deviceNum) {
    if (cap.isOpened()) {
        cap.set(cv::CAP_PROP_FRAME_WIDTH, width);
        cap.set(cv::CAP_PROP_FRAME_HEIGHT, height);
    } else {
        std::cout << "No input device.\n";
    }
}

void circle_detector::detect_circles(const cv::Size &blur_size, const int &min_radius, const int &max_radius) {
    circles.clear();
    cap >> frame;
    cv::cvtColor(frame, gray, cv::COLOR_BGR2GRAY);
    cv::GaussianBlur(gray, gray, blur_size, 0);
    cv::HoughCircles(gray, circles, cv::HOUGH_GRADIENT, 1, gray.rows / 8, 100, 20, min_radius, max_radius);
}

const std::vector<cv::Point> &circle_detector::locate_circles() {
    points.clear();

    if (circles.size() > 0) {
        for (uint8_t i = 0; i < circles.size(); i++) {
            cv::Point point = cv::Point(cvRound(circles[i][0]), cvRound(circles[i][1]));
            if ((point.x + point.y) > 0) {
                std::cout << circles[i] << "\n";
                points.push_back(point);
            }
        }
    }

    return points;
}

void circle_detector::display_circles(const std::string &window_name) {
    if (points.size() > 0) {
        for (uint8_t i = 0; i < points.size(); i++) {
            cv::circle(frame, points[i], 3, cv::Scalar(0, 255, 0), -1, 8, 0);
        };
    }
    cv::imshow(window_name, frame);
}