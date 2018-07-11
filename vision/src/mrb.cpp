#include "mrb.hpp"

MRB_controller::MRB_controller(const std::string &window_name, const uint8_t &deviceNum, const uint16_t &width,
                               const uint16_t &height)
    : window_name{window_name}, cap{deviceNum}, triangle_detected{false} {
    cv::namedWindow(window_name, cv::WINDOW_AUTOSIZE);
    cv::setMouseCallback(window_name, this->mouse_handler, this);

    if (cap.isOpened()) {
        cap.set(cv::CAP_PROP_FRAME_WIDTH, width);
        cap.set(cv::CAP_PROP_FRAME_HEIGHT, height);
    } else {
        std::cout << "No input device.\n";
    }
}

// Private
void MRB_controller::mouse_handler(int evt, int x, int y, int flags, void *param) {
    if (evt == cv::EVENT_LBUTTONDOWN) {
        MRB_controller *mrb = static_cast<MRB_controller *>(param);
        if (mrb) {
            mrb->new_set_point(cv::Point(x, y));
        }
    }
}

// Public
bool MRB_controller::init(Circle_detector &circles, std::vector<cv::Point> &servo_positions) {
    renew_frame();
    imshow(window_name, frame);
    while (servo_positions.size() < 4) {
        std::cout << "Press 'a' for automatic servo localisation.\n"
                  << "Press 'm' for manual servo loacalisation.\n"
                  << "Press 'q' to quit.\n";

        char key = cv::waitKey(0);

        if (key == 'a') {
            std::cout << "Automatic servo loacalisation.\n"
                      << "Make sure the servo stickers are visible to the camera.\n";
            servo_positions = circles.init(cv::Size(17, 17), 0, 10);
        } else if (key == 'm') {
            std::cout << "Manual servo localisation.\n"
                      << "Click with the mouse in the video feed on the locations of the servos.\n";

            std::cout << "Click the red motor.\n";
            servo_positions.push_back(get_mouse_pos_on_click());
            std::cout << "Red: " << servo_positions[0] << '\n';

            std::cout << "Click the blue motor.\n";
            servo_positions.push_back(get_mouse_pos_on_click());
            std::cout << "blue: " << servo_positions[1] << '\n';

            std::cout << "Click the green motor.\n";
            servo_positions.push_back(get_mouse_pos_on_click());
            std::cout << "green: " << servo_positions[2] << '\n';

            if (MRB_MATH::triangle_check(servo_positions[0], servo_positions[1], servo_positions[2], 20)) {
                std::cout << "Valid motor positions detected.\n";
                return 1;
            } else {
                std::cout << "Invalid motor positions detected.\n";
                servo_positions.clear();
            }
        } else if (key == 'q') {
            return 0;
        }
    }

    return 0;
}

void MRB_controller::display_circles(std::vector<cv::Point> &points) const {
    if (points.size() > 0) {
        for (uint8_t i = 0; i < points.size(); i++) {
            cv::circle(frame, points[i], 3, cv::Scalar(0, 255, 0), -1, 8, 0);
        };
    }
}

void MRB_controller::set_pid_controllers(std::vector<PID> &pid_controllers) {
    for (uint8_t i = 0; i < pid_controllers.size(); ++i) {
        PID_ctrls.push_back(&pid_controllers[i]);
    }
}

void MRB_controller::display_set_point() {
    cv::circle(frame, set_point, 3, cv::Scalar(255, 255, 0), -1, 8, 0);
}

void MRB_controller::new_set_point(const cv::Point &new_pos) {
    std::cout << "New set_point & reset PID.\n";

    set_point = new_pos;
    for (auto &v : PID_ctrls) {
        if (v != nullptr) {
            v->reset();
        }
    }
}

void MRB_controller::renew_frame() {
    cap >> frame;
}

cv::Mat &MRB_controller::get_frame() {
    return frame;
}

cv::VideoCapture &MRB_controller::get_cap() {
    return cap;
}

std::string &MRB_controller::get_window_name() {
    return window_name;
}

cv::Point &MRB_controller::get_mouse_pos() {
    return set_point;
}

cv::Point &MRB_controller::get_mouse_pos_on_click() {
    cv::Point temp = set_point;
    while (temp == set_point) {
        cv::waitKey(100);
    }
    return set_point;
}

bool &MRB_controller::get_triangle_detected() {
    return triangle_detected;
}
