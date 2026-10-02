#include "stdint.h"

#pragma once

struct MotorPins {
  uint8_t pwm;
  uint8_t dir;
};

struct MotorConstants {
  int maxChange;
};

class Motor {
public:
  explicit Motor(MotorPins pins, MotorConstants constants);
  void begin();
  
  void update();

  void setSpeed(int speed);
  void up();
  void down();
  void stop();
  void stopInstant();

  int speed() const;
  bool isMovingDown() const;

private:
  struct State {
    int target;
    int actual;
  };

  MotorPins pins;
  MotorConstants constants;
  State state;

  void apply();
};