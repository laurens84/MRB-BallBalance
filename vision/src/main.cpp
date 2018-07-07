#include "UART.hpp"
#include "circle_detector.hpp"
#include "coordinator.hpp"
#include "display.hpp"
#include "pid.hpp"
#include "servo.hpp"
#include <stdio.h>

bool triangle_check(const cv::Point &red, const cv::Point &blue, const cv::Point &green) {
    double side_1 = sqrt(pow(red.x - blue.x, 2) + pow(red.y - blue.y, 2));
    double side_2 = sqrt(pow(red.x - green.x, 2) + pow(red.y - green.y, 2));
    double side_3 = sqrt(pow(blue.x - green.x, 2) + pow(blue.y - green.y, 2));
    double side_avg = (side_1 + side_2 + side_3) / 3;

    if ((side_1 - side_avg > -10) && (side_1 - side_avg < 10)) {
        return true;
    } else
        return false;
}

int main() {

    // Circle detection.
    display window("Circles");
    Circle_detector circles(0, 100, 100);

    // Get motor position.
    std::vector<cv::Point> servo_positions;

    while (servo_positions.size() != 3) {
        std::cout << "Press 'a' for automatic servo localisation.\n"
                  << "Press 'm' for manual servo loacalisation.\n";
        char key = cv::waitKey(0);
        if (key == 'a') {
            std::cout << "Automatic servo loacalisation.\n"
                      << "Make sure the servo stickers are visible to the camera.\n";
            servo_positions = circles.init(cv::Size(17, 17), 0, 10);
        } else if (key == 'm') {
            std::cout << "Manual servo localisation.\n"
                      << "Click with the mouse in the video feed on the locations of the servos.\n";
            std::cout << "Click the red motor.\n";
            servo_positions.push_back(window.get_mouse_pos_on_click());
            std::cout << "Red: " << servo_positions[0] << '\n';

            std::cout << "Click the blue motor.\n";
            servo_positions.push_back(window.get_mouse_pos_on_click());
            std::cout << "blue: " << servo_positions[1] << '\n';

            std::cout << "Click the green motor.\n";
            servo_positions.push_back(window.get_mouse_pos_on_click());
            std::cout << "green: " << servo_positions[2] << '\n';

            if (triangle_check(servo_positions[0], servo_positions[1], servo_positions[2]))
                std::cout << "Valid motor positions detected.\n";
            else {
                std::cout << "Invalid motor positions detected.\n";
                return 1;
            }
        }
    }

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