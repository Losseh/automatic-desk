#include "stdint.h"
#pragma once

struct CurrentSensorParams {
  int zeroValue;
  int samples;
  int previousAverageWeight;
};

class CurrentSensor {
public:
  explicit CurrentSensor(int pin, CurrentSensorParams params);
  void measure();
  int previous() const;
  int movingAverage() const;

private:
  struct State {
    int previous;
    int movingAverage;
  };

  int pin;
  CurrentSensorParams params;
  State state;
};