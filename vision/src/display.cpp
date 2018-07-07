#include "display.hpp"

void display::mouse_handler(int evt, int x, int y, int flags, void *param) {
    if (evt == cv::EVENT_LBUTTONDOWN) {
        cv::Point *ptr = (cv::Point *)param;
        ptr->x = x;
        ptr->y = y;
        // std::cout << *ptr << '\n';
    }
}

display::display(const std::string &window_name) : window_name{window_name} {
    cv::namedWindow(window_name, cv::WINDOW_AUTOSIZE);
    cv::setMouseCallback(window_name, this->mouse_handler, (void *)&set_point);
}

void display::display_circles(cv::Mat &frame, std::vector<cv::Point> &points) const {
    if (points.size() > 0) {
        for (uint8_t i = 0; i < points.size(); i++) {
            cv::circle(frame, points[i], 3, cv::Scalar(0, 255, 0), -1, 8, 0);
        };
    }
    cv::imshow(window_name, frame);
}

cv::Point &display::get_mouse_pos() {
    return set_point;
}

cv::Point &display::get_mouse_pos_on_click() {
    cv::Point temp = set_point;
    while (temp == set_point) {
        cv::waitKey(100);
    }
    return set_point;
}

void display::set_mouse_pos(const cv::Point &mouse_pos) {
    set_point = mouse_pos;
}