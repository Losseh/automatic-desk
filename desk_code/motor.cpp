#include "motor.h"
#include "Arduino.h"

#define MAX_PWM 255

Motor::Motor(MotorPins pins, MotorConstants constants): pins(pins), constants(constants), state({0, 0}) {}

void Motor::begin() {
  pinMode(pins.pwm, OUTPUT);
  pinMode(pins.dir, OUTPUT);
  forceStop();
}

void Motor::update() {
  int diff = state.target - state.actual;

  if (abs(diff) < constants.maxChange) {
    state.actual = state.target;
  } else if (diff > 0) {
    state.actual += constants.maxChange;
  } else if (diff < 0) {
    state.actual -= constants.maxChange;
  }

  state.actual = constrain(state.actual, -MAX_PWM, MAX_PWM);

  // if (diff != 0) {
  //   Serial.write("motor exp=");
  //   Serial.print(state.target);
  //   Serial.write(" act=");
  //   Serial.print(state.actual);
  //   Serial.write("\n");
  // }

  apply();
}

void Motor::setSpeed(int speed) {
  state.target = constrain(speed, -MAX_PWM, MAX_PWM);
}

void Motor::forceStop() {
  state.actual = 0;
  state.target = 0;
  apply();

  Serial.write("motor stopped\n");
}

int Motor::speed() const {
  return state.actual;
}

bool Motor::isMovingDown() const {
  return state.actual < 0;
}

void Motor::apply() {
  int pwm = abs(state.actual);
  uint8_t dir = state.actual >= 0 ? HIGH : LOW;

  digitalWrite(pins.dir, dir);
  analogWrite(pins.pwm, pwm);
}