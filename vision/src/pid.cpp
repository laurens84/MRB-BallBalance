#include "pid.hpp"

PID::PID(const double &dt, const double &max, const double &min, const double &Kp, const double &Ki, const double &Kd)
    : _dt{dt}, _max{max}, _min{min}, _Kp{Kp}, _Ki{Ki}, _Kd{Kd}, _pre_error{0}, _integral{0} {
}

double PID::calculate(const double &error) {
    // Proportional term
    double Pout = _Kp * error;

    // Integral term
    _integral += error * _dt;
    double Iout = _Ki * _integral;

    // Derivative term
    double derivative = (error - _pre_error) / _dt;
    double Dout = _Kd * derivative;

    // Calculate total output
    double output = Pout + Iout + Dout + ((_max + _min) * 0.5f);
 
    // Save error to previous error
    // Restrict to max/min
    if (output > _max)
        output = _max;
    else if (output < _min)
        output = _min;

    _pre_error = error;
    return output;
}

void PID::reset() {
    _pre_error = 0;
    _integral = 0;
}
