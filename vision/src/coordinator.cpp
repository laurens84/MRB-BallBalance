#include "coordinator.hpp"

cv::Point &Coordinator::get_servo_location(const uint8_t &id) {
    for (const auto &i : servos) {
        if (i->get_id() == id) {
            return i->get_position();
        }
    }
    return servos[0]->get_position(); // slecht
}