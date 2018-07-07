#ifndef _PID_HPP_
#define _PID_HPP_

class PIDImpl;
class PID {
  public:
    // Kp -  proportional gain
    // Ki -  Integral gain
    // Kd -  derivative gain
    // dt -  loop interval time
    // max - maximum value of manipulated variable
    // min - minimum value of manipulated variable
    PID(double dt, double max, double min, double Kp, double Kd, double Ki);

    // Returns the manipulated variable given a setpoint and current process value
    double calculate(double setpoint, double pv);
    double calculate(double error);
    ~PID();

  private:
    PIDImpl *pimpl;
};

#endif