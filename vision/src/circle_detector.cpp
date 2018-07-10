#include "circle_detector.hpp"
#include "mrb.hpp"

Circle_detector::Circle_detector(MRB_controller *MRB_ctrl) : MRB_ctrl{MRB_ctrl} {
}

std::vector<cv::Point> Circle_detector::init(const cv::Size &blur_size, const int &min_radius, const int &max_radius) {
    while (!MRB_ctrl->get_triangle_detected()) {
        cv::Point red(0, 0), blue(0, 0), green(0, 0);

        MRB_ctrl->renew_frame();
        imshow(MRB_ctrl->get_window_name(), MRB_ctrl->get_frame());

        cv::Mat frame = MRB_ctrl->get_frame();

        cv::Mat3b bgr_inv = ~frame;
        cv::Mat3b hsv_inv;
        cv::cvtColor(bgr_inv, hsv_inv, cv::COLOR_BGR2HSV); // Red
        cv::cvtColor(frame, frame, cv::COLOR_BGR2HSV);     // Blue & green.

        // Red
        inRange(hsv_inv, cv::Scalar(80, 70, 50), cv::Scalar(100, 255, 220), mask);
        cv::GaussianBlur(mask, mask, blur_size, 0);
        cv::HoughCircles(mask, circles, cv::HOUGH_GRADIENT, 1, mask.rows / 8, 100, 20, min_radius, max_radius);
        if (circles.size() > 0)
            red = cv::Point(cvRound(circles[0][0]), cvRound(circles[0][1]));
        std::cout << "Red: " << red << '\n';

        // Blue
        circles.clear();
        inRange(frame, cv::Scalar(100, 70, 75), cv::Scalar(110, 255, 220), mask);
        cv::GaussianBlur(mask, mask, blur_size, 0);
        cv::HoughCircles(mask, circles, cv::HOUGH_GRADIENT, 1, mask.rows / 8, 100, 20, min_radius, max_radius);
        if (circles.size() > 0)
            blue = cv::Point(cvRound(circles[0][0]), cvRound(circles[0][1]));
        std::cout << "Blue: " << blue << '\n';

        // Green
        circles.clear();
        inRange(frame, cv::Scalar(60, 70, 75), cv::Scalar(90, 255, 220), mask);
        cv::GaussianBlur(mask, mask, blur_size, 0);
        cv::HoughCircles(mask, circles, cv::HOUGH_GRADIENT, 1, mask.rows / 8, 100, 20, min_radius, max_radius);
        if (circles.size() > 0)
            green = cv::Point(cvRound(circles[0][0]), cvRound(circles[0][1]));
        std::cout << "Green: " << green << '\n';

        if ((red.x != 0 && red.y != 0) && (blue.x != 0 && blue.y != 0) && (green.x != 0 && green.y != 0)) {
            if (MRB_MATH::triangle_check(red, blue, green, 20)) {
                MRB_ctrl->get_triangle_detected() = true;
                return {red, blue, green};
            };
        }

        if (cv::waitKey(30) == 'c') {
            break;
        }
    }

    return {cv::Point(-1, -1)};
}

void Circle_detector::detect_circles(const cv::Size &blur_size, const int &min_radius, const int &max_radius) {
    circles.clear();
    MRB_ctrl->renew_frame();
    cv::cvtColor(MRB_ctrl->get_frame(), gray, cv::COLOR_BGR2GRAY);
    cv::GaussianBlur(gray, gray, blur_size, 1.5);
    cv::HoughCircles(gray, circles, cv::HOUGH_GRADIENT, 2, gray.rows / 4, 100, 40, min_radius, max_radius);
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

std::vector<cv::Vec3f> &Circle_detector::get_circles() {
    return circles;
}

std::vector<cv::Point> &Circle_detector::get_circle_points() {
    return points;
}