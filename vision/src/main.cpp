#include "UART.hpp"
#include "circle_detector.hpp"
#include "coordinator.hpp"
#include "display.hpp"
#include "pid.hpp"
#include "servo.hpp"
#include <stdio.h>

int main() {

    // Circle detection.
    display window("Circles");
    Circle_detector circles(0, 800, 800);

    // Detect motor position.
    auto servo_positions = circles.init(cv::Size(17, 17), 0, 10);

    if (servo_positions[0] == cv::Point(-1, -1)) {
        std::cout << "TERMINATED\n";
        return 0;
    }

    UART serial("/dev/ttyUSB0");
    serial.connect();

    Servo servo1(serial, 'a', servo_positions[0]);
    Servo servo2(serial, 'b', servo_positions[1]);
    Servo servo3(serial, 'c', servo_positions[2]);

    sleep(2);

    servo1.write(110);
    usleep(10000);
    servo2.write(110);
    usleep(10000);
    servo3.write(110);

    Coordinator<3> cod(&servo1, &servo2, &servo3);

    std::cout << *cod.get_servo_location('a') << "\n";

    window.set_mouse_pos((1.f / 3.f) * (servo1.get_position() + servo2.get_position() + servo3.get_position()));

    PID pid1 = PID(0.1, 105, 85, 0.0000001, 1.5, 0.0005);
    PID pid2 = PID(0.1, 105, 85, 0.0000001, 1.5, 0.0005);
    PID pid3 = PID(0.1, 105, 85, 0.0000001, 1.5, 0.0005);

    while (1) {
        circles.detect_circles(cv::Size(17, 17), 0, 40);
        if (circles.get_circles().size() > 0) {
            circles.locate_circles();

            std::array<double, 3> errors = cod.calcError(window.get_mouse_pos(), circles.get_circle_points()[0]);

            servo1.write((int)pid1.calculate(errors[0]));
            usleep(10000);
            servo2.write((int)pid2.calculate(errors[1]));
            usleep(10000);
            servo3.write((int)pid3.calculate(errors[2]));
            usleep(10000);
        }
        window.display_circles(circles.get_frame(), circles.get_circle_points());

        if (cv::waitKey(30) == 'c') {
            break;
        }
    }

    return 0;
}