#include "circle_detector.hpp"
#include "coordinator.hpp"
#include <stdio.h>

int main() {
    // Circle detection.
    Circle_detector circles(1, 500, 400);
    Coordinator cod;
    cv::namedWindow("Circles", cv::WINDOW_AUTOSIZE);

    // Detect motor position.
    circles.init(cod, cv::Size(17, 17), 0, 10);
    std::vector<cv::Point> servo_locations = circles.locate_circles();

    // Coordinator class.
    std::cout << servo_locations << std::endl;

    while (1) {
        circles.init(cod, cv::Size(17, 17), 0, 10);
        circles.locate_circles();
        circles.display_circles("Circles");
        if (cv::waitKey(30) == 'c')
            break;
    }

    return 0;
}