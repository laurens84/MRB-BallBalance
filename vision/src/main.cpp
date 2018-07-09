#include "UART.hpp"
#include "mrb_math.hpp"
#include "mrb.hpp"
#include "circle_detector.hpp"
#include "coordinator.hpp"
#include "pid.hpp"
#include "servo.hpp"
#include <stdio.h>

int main() {
    // MRB controller.
    MRB_controller mrb("Circles", 0, 400, 400);

    // Circle detection.
    Circle_detector circles(&mrb);

    // Store the motor positions.
    std::vector<cv::Point> servo_positions;

    if(!mrb.init(circles, servo_positions)){
        std::cerr << "INIT TERMINATED\n";
        return 1;
    }

    // Init serial
    UART serial("/dev/ttyUSB0");
    serial.connect();

    // Init servos with the serial, an ID and the servo's position.
    Servo servo1(serial, 'a', servo_positions[0]);
    Servo servo2(serial, 'b', servo_positions[1]);
    Servo servo3(serial, 'c', servo_positions[2]);

    // Init the Coordinator object with 3 servos.
    Coordinator<3> cod(&servo1, &servo2, &servo3);

    std::cout << *cod.get_servo_location('a') << "\n";

    // Set the set_point in the center.
    mrb.set_mouse_pos((1.f / 3.f) * (servo1.get_position() + servo2.get_position() + servo3.get_position()));

    // Create PID objects.
    PID pid1 = PID(1, 120, 70, 0.00001, 1.5, 0.0005);
    PID pid2 = PID(1, 120, 70, 0.00001, 1.5, 0.0005);
    PID pid3 = PID(1, 120, 70, 0.00001, 1.5, 0.0005);

    while (1) {
        circles.detect_circles(cv::Size(13, 13), 20, 30);

        if (circles.get_circles().size() > 0) {
            circles.locate_circles();

            if(circles.get_circle_points().size() > 0){
                std::array<double, 3> errors = cod.calcError(mrb.get_mouse_pos(), circles.get_circle_points()[0]);

                servo1.write((int)pid1.calculate(errors[0]));
                usleep(10000);
                servo2.write((int)pid2.calculate(errors[1]));
                usleep(10000);
                servo3.write((int)pid3.calculate(errors[2]));
                usleep(10000);
            }
        }

        mrb.display_circles(circles.get_circle_points());

        if (cv::waitKey(30) == 'c') {
            break;
        }
    }

    return 0;
}
