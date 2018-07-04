#include "UART.hpp"
#include "circle_detector.hpp"
#include "coordinator.hpp"
#include "display.hpp"
#include "servo.hpp"
#include <stdio.h>

int main() {

    // Circle detection.
    display window("Circles");
    Circle_detector circles(0, 800, 800);

    // Detect motor position.
    auto servo_positions = circles.init(cv::Size(17, 17), 0, 10);

    if (servo_positions[0] == cv::Point(0, 0)) {
        std::cout << "Appels\n";
        return 0;
    }

    UART serial("/dev/ttyUSB0");
    serial.connect();

    Servo servo1(serial, 'a', servo_positions[0]);
    Servo servo2(serial, 'b', servo_positions[1]);
    Servo servo3(serial, 'c', servo_positions[2]);

    sleep(2);

    servo1.write(80);    
    usleep(10000);
    servo2.write(80);
    usleep(10000);
    servo3.write(80);

    Coordinator<3> cod(&servo1, &servo2, &servo3);

    std::cout << *cod.get_servo_location('a') << "\n";

    while (1) {
        circles.detect_circles(cv::Size(17, 17), 0, 40);
        circles.locate_circles();
        window.display_circles(circles.get_frame(), circles.get_circle_points());

        if (cv::waitKey(30) == 'c') {
            break;
        }
    }

    return 0;
}