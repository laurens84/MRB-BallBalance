#include "UART.hpp"
#include "circle_detector.hpp"
#include "coordinator.hpp"
#include "mrb.hpp"
#include "mrb_math.hpp"
#include "pid.hpp"
#include "servo.hpp"
#include <stdio.h>

int main() {
    // MRB controller.
    MRB_controller mrb("Circles", 0, 300, 300);

    // Circle detection.
    Circle_detector circles(&mrb);

    // Storage for the motor positions.
    std::vector<cv::Point> servo_positions;

    if (!mrb.init(circles, servo_positions)) {
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
    mrb.new_set_point((1.f / 3.f) * (servo1.get_position() + servo2.get_position() + servo3.get_position()));
    mrb.display_set_point();

    // Create PID objects.
    double p = 0.09;
    double i = 0.0;
    double d = 0.9;

    PID pid1 = PID(0.1, 100, 57, p, i, d);
    PID pid2 = PID(0.1, 108, 70, p, i, d);
    PID pid3 = PID(0.1, 110, 70, p, i, d);

    // Set the PID object pointers in mrb to enable properly changing the SP on click.
    std::vector<PID> PID_vec = {pid1, pid2, pid3};
    mrb.set_pid_controllers(PID_vec);

    while (1) {
        mrb.renew_frame();
        circles.detect_circles(cv::Size(9, 9), 20, 30);

        if (circles.get_circles().size() > 0) {
            circles.locate_circles();

            if (circles.get_circle_points().size() > 0) {
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
        mrb.display_set_point();
        imshow(mrb.get_window_name(), mrb.get_frame());

        if (cv::waitKey(30) == 'q') {
            break;
        }
    }

    return 0;
}
