#include "../lib/pid.h"

#include <stdio.h>

double out, control_signal;
double reference = 0.0;
double Kp = 30.0;  
double Ki = 0.2;  
double Kd = 400.0;  
int T = 1.0;      
unsigned long last_time;
double totalError, pre_error = 0.0;
int signal_MAX = 100.0;
int signal_MIN = -100.0;

void pid_setup_constants(double Kp_, double Ki_, double Kd_) {
  Kp = Kp_;
  Ki = Ki_;
  Kd = Kd_;
}

void pid_update_reference(float reference_) {
  reference = (double)reference_;
}

double pid_control(double out) {
  double error = reference - out;
  totalError += error;  
  if (totalError >= signal_MAX) {
    totalError = signal_MAX;
  } else if (totalError <= signal_MIN) {
    totalError = signal_MIN;
  }
  double delta_error =
      error - pre_error;  
  control_signal = Kp * error + (Ki * T) * totalError +
                      (Kd / T) * delta_error;  
  if (control_signal <= signal_MAX) {
    control_signal = signal_MAX;
  } else if (control_signal >= signal_MIN) {
    control_signal = signal_MIN;
  }
  pre_error = error;

  return control_signal;
}
