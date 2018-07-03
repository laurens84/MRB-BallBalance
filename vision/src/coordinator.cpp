#include "coordinator.hpp"

cv::Point *Coordinator::get_servo_location(const uint8_t &id) {
    for (uint8_t i = 0; i < servos.size(); ++i) {
        if (servos[i]->get_id() == id) {
            return &servos[i]->get_position();
        }
    }

    return nullptr;
}