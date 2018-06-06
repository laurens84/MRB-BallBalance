#include "circle_detector.hpp"
#include "coordinator.hpp"
#include <stdio.h>

int main() {
    circle_detector circles(1, 500, 400);
    cv::namedWindow("Circles", cv::WINDOW_AUTOSIZE);

    circles.detect_circles();
    std::vector<cv::Point> servo_locations = circles.locate_circles();

    // Coordinator class
    std::cout << servo_locations << std::endl;

    while (1) {
        circles.detect_circles();
        circles.locate_circles();
        circles.display_circles("Circles");
        if (cv::waitKey(30) == 'c')
            break;
    }

    return 0;
}