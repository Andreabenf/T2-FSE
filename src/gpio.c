#include "../inc/gpio.h"
#include <softPwm.h>
#include <wiringPi.h>

#define RESISTOR_PIN 4
#define AF_PIN 5

void turn_resistance_on(int new_resistor_value) {
  pinMode(RESISTOR_PIN, OUTPUT);
  softPwmCreate(RESISTOR_PIN, 0, 100);
  softPwmWrite(RESISTOR_PIN, new_resistor_value);
}

void turn_resistance_off() {
  pinMode(RESISTOR_PIN, OUTPUT);
  softPwmCreate(RESISTOR_PIN, 0, 100);
  softPwmWrite(RESISTOR_PIN, 0);
}

void turn_on(int new_af_value) {
  pinMode(AF_PIN, OUTPUT);
  softPwmCreate(AF_PIN, 0, 100);
  softPwmWrite(AF_PIN, new_af_value);
}

void turn_off() {
  pinMode(AF_PIN, OUTPUT);
  softPwmCreate(AF_PIN, 0, 100);
  softPwmWrite(AF_PIN, 0);
}

void pwm_control(int intensity_signal) {
  if (intensity_signal > 0) {
    turn_resistance_on(intensity_signal);
    turn_off();
  } else {
    if (intensity_signal <= -40)
      turn_on(intensity_signal * -1);
    else
      turn_off();
    turn_resistance_off();
  }
}
