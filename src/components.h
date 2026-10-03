#pragma once

#include "button.h"
#include "motor.h"
#include "limit_switch.h"
#include "current_sensor.h"

struct Components {
  Button& upBtn;
  Button& downBtn;
  Motor& motor;
  LimitSwitch& lowerLimitSwitch;
  CurrentSensor& currentSensor;
};