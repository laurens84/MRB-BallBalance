#ifndef COORDINATOR_HPP
#define COORDINATOR_HPP

#include "circle_detector.hpp"
#include "servo.hpp"

template<uint8_t NUM_SERVOS>
class Coordinator {
  private:
    std::array<Servo *, NUM_SERVOS> servos;
    cv::Point set_point;

  public:
    
  Coordinator(Servo *servo_a, Servo *servo_b, Servo *servo_c) : 
      servos{servo_a, servo_b, servo_c},
      set_point{(1.f / 3.f) * (servo_a->get_position() + servo_b->get_position() + servo_c->get_position())}
  { std::cout << "sp: " << set_point << '\n'; }

  std::array<int32_t, NUM_SERVOS> calcError(const cv::Point & ball_pos){
      std::array<int32_t, NUM_SERVOS> error;
      
      for(uint8_t i = 0; i < servos.size(); ++i){
          //if()
      }

      return error;
  }

  cv::Point *get_servo_location(const uint8_t &id) {
      for (uint8_t i = 0; i < servos.size(); ++i) {
          if (servos[i]->get_id() == id) {
              return &servos[i]->get_position();
          }
      }

      return nullptr;
  }
};

#endif // COORDINATOR_HPP