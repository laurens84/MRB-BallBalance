#ifndef PID_HPP
#define PID_HPP

#include <iostream>

class PID {
  private:
    double _dt;
    double _max;
    double _min;
    double _Kp;
    double _Kd;
    double _Ki;
    double _pre_error;
    double _integral;

  public:
    // Kp -  proportional gain
    // Ki -  Integral gain
    // Kd -  derivative gain
    // dt -  loop interval time
    // max - maximum value of manipulated variable
    // min - minimum value of manipulated variable
    PID(const double &dt, const double &max, const double &min, const double &Kp, const double &Kd, const double &Ki);

    // Returns the manipulated variable given an error value.
    // Double calculate(const double & error);
    double calculate(const double &error);

    void reset();
};

#endif // PID_HPP
