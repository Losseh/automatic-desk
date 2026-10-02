#include "current_sensor.h"
#include "Arduino.h"

CurrentSensor::CurrentSensor(int pin, CurrentSensorParams params): 
    pin(pin), 
    params(params),
    state({params.zeroValue, params.zeroValue})
    {}

void CurrentSensor::measure() {

  int previousTmp = 0;
  for (int i = 0; i < params.samples; i++) {
    previousTmp += analogRead(pin);
  }
  state.previous = previousTmp / params.samples - params.zeroValue;
  state.movingAverage = (params.previousAverageWeight * state.movingAverage + state.previous) / (params.previousAverageWeight + 1);
}

int CurrentSensor::previous() const {
  return state.previous;
}

int CurrentSensor::movingAverage() const {
  return state.movingAverage;
}