#include "circle_detector.hpp"
#include "display.hpp"
#include <stdio.h>

int main() {

    // Circle detection.
    display window("Circles");
    Circle_detector circles(0, 500, 400);

    // Detect motor position.
    auto servo_positions = circles.init(cv::Size(17, 17), 0, 10);

    for (uint8_t i = 0; i < servo_positions.size(); ++i) {
        std::cout << servo_positions[i] << std::endl;
    }

    // UART
    // Servos aanmaken met UART.

    // Coordinator cod;
    // Add servos& to coordinator array.

    while (1) {
        circles.detect_circles(cv::Size(17, 17), 0, 40);
        circles.locate_circles();
        window.display_circles(circles.getFrame(), circles.getCirclePoints());

        if (cv::waitKey(30) == 'c')
            break;
    }

    return 0;
}