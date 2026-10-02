#include "stdint.h"

#pragma once

class LimitSwitch {
public:
  LimitSwitch(uint8_t pin);

  void begin();

  bool isPressed() const;

private:
  uint8_t pin;
};