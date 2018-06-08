#include "circle_detector.hpp"
#include "coordinator.hpp"
#include <stdio.h>

int main() {

    // Circle detection.
    circle_detector circles(1, 500, 400);
    cv::namedWindow("Circles", cv::WINDOW_AUTOSIZE);

    // Detect motor position.
    // 0, 10 for motor circles.
    circles.detect_circles(cv::Size(17, 17), 0, 10);
    std::vector<cv::Point> servo_locations = circles.locate_circles();

    // Coordinator class.
    std::cout << servo_locations << std::endl;

    while (1) {
        circles.detect_circles(cv::Size(17, 17), 20, 30);
        circles.locate_circles();
        circles.display_circles("Circles");
        if (cv::waitKey(30) == 'c')
            break;
    }

    return 0;
}