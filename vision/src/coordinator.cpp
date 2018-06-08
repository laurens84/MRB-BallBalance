#include "coordinator.hpp"

void Coordinator::setServos(Servo *servo_a, Servo *servo_b, Servo *servo_c) {
    if (!has_servos) {
        servos[0] = servo_a;
        servos[1] = servo_b;
        servos[2] = servo_c;
        has_servos = true;
    }
}
