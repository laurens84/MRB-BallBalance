#include "coordinator.hpp"

void Coordinator::setServos(std::unique_ptr<Servo> servo_a, std::unique_ptr<Servo> servo_b, std::unique_ptr<Servo> servo_c) {
    if (!has_all_servos) {
        servos[0] = std::move(servo_a);
        servos[1] = std::move(servo_b);
        servos[2] = std::move(servo_c);
        has_all_servos = true;
    }
}
