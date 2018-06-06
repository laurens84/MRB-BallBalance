#include "circle_detector.hpp"

circle_detector::circle_detector(const uint8_t &deviceNum, const uint16_t &width, const uint16_t &height) : cap(deviceNum) {
    if (cap.isOpened()) {
        cap.set(cv::CAP_PROP_FRAME_WIDTH, width);
        cap.set(cv::CAP_PROP_FRAME_HEIGHT, height);
    } else {
        std::cout << "No input device.\n";
    }
}

void circle_detector::init() {
}

void circle_detector::detect_circles() {
    circles.clear();
    cap >> frame;
    cv::cvtColor(frame, gray, cv::COLOR_BGR2GRAY);
    cv::GaussianBlur(gray, gray, cv::Size(17, 17), 0);
    cv::HoughCircles(gray, circles, cv::HOUGH_GRADIENT, 1, gray.rows / 4, 100, 20, 0, 10);
}

const std::vector<cv::Point> &circle_detector::locate_circles() {
    points.clear();
    points.resize(circles.size());

    for (uint8_t i = 0; i < circles.size(); i++) {
        points[i] = cv::Point(cvRound(circles[i][0]), cvRound(circles[i][1]));
    }

    return points;
}

void circle_detector::display_circles(const std::string &window_name) {
    if (points.size() > 0) {
        std::cout << points.size() << "\n";
        for (uint8_t i = 0; i < points.size(); i++) {
            cv::circle(frame, points[i], 3, cv::Scalar(0, 255, 0), -1, 8, 0);
        };
    }
    cv::imshow(window_name, frame);
}