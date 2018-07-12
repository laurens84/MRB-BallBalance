/**
 * @brief The PID file contains the PID class used to manipulate values based on the error.
 *
 * @file pid.hpp
 * @date 2018-07-11
 */
#ifndef PID_HPP
#define PID_HPP

#include <iostream>

class PID {
  private:
    double _dt;
    double _max;
    double _min;
    double _Kp;
    double _Ki;
    double _Kd;
    double _pre_error;
    double _integral;

  public:
    /**
     * @brief Construct a new PID controller object.
     *
     * @param dt  loop interval time.
     * @param max maximum value of manipulated variable.
     * @param min minimum value of manipulated variable.
     * @param Kp  proportional gain.
     * @param Ki  Integral gain.
     * @param Kd  derivative gain.
     */
    PID(const double &dt, const double &max, const double &min, const double &Kp, const double &Ki, const double &Kd);

    /**
     * @brief Manipulates a given error using the pid controller algorithm.
     *
     * @param error   The error between the SP and the PV.
     * @return double The manipulated value.
     */
    double calculate(const double &error);

    /**
     * @brief Resets the _pre_error and _integral to avoid problems when a new SP is set.
     *
     */
    void reset();
};

#endif // PID_HPP
