#include "command_state.h"
#include "short_pressed_command_state.h"
#include "Arduino.h"

ShortPressedCommandState::ShortPressedCommandState(CommandStatePool& commandStatePool, Button& upBtn, Button& downBtn, 
  Motor& motor, LimitSwitch& lowerLimitSwitch) : 
  commandStatePool(commandStatePool),
  upBtn(upBtn),
  downBtn(downBtn),
  motor(motor),
  lowerLimitSwitch(lowerLimitSwitch)
  {}

void ShortPressedCommandState::init(const StateContext& stateContext) {
  this->direction = stateContext.direction;
}

StateTransition ShortPressedCommandState::update(StateContext& stateContext) {
  // any button pressed -> end of short-press
  bool upPressed = upBtn.isPressed();
  if (upPressed || downBtn.isPressed()) {
    motor.stop();

    Serial.write("short-pressed -> wait-for-release\n");
    return {
      commandStatePool.waitForRelease,
      { upPressed ? Direction::UP : Direction::DOWN }
    };
  }

  // TODO aszymanski: stop instant should happen also when current exceeds the limit
  switch (stateContext.direction) {
    case Direction::UP:
      motor.up();
      break;

    case Direction::DOWN:
      if (lowerLimitSwitch.isPressed()) {
        motor.stopInstant();
        return {
          commandStatePool.idle,
          {}
        };
      } else {
        motor.down();
      }
      break;

    // Serial.write("short-pressed -> short-pressed\n");
    return {
      this,
      stateContext
    };
  }


  // Serial.write("short-pressed -> short-pressed\n");
  return {
    this,
    stateContext
  };
}