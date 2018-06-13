#include "circle_detector.hpp"
#include "coordinator.hpp"
#include "display.hpp"
#include <stdio.h>

int main() {

    // Circle detection.
    display window("Circles");
    Circle_detector circles(1, 500, 400);
    Coordinator cod;

    // Detect motor position.
    circles.init(cod, cv::Size(17, 17), 0, 10);
    std::vector<cv::Point> servo_locations = circles.locate_circles();

    // Coordinator class.
    std::cout << servo_locations << std::endl;

    while (1) {
        circles.detect_circles(cv::Size(17, 17), 0, 40);
        circles.locate_circles();
        window.display_circles(circles.getFrame(), circles.getCirclePoints());

        if (cv::waitKey(30) == 'c')
            break;
    }

    return 0;
}