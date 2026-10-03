#include "command_state.h"
#include "long_pressed_command_state.h"
#include "Arduino.h"

LongPressedCommandState::LongPressedCommandState(CommandStatePool& commandStatePool, Button& upBtn, Button& downBtn, 
  Motor& motor, LimitSwitch& lowerLimitSwitch) : 
  commandStatePool(commandStatePool),
  upBtn(upBtn),
  downBtn(downBtn),
  motor(motor),
  lowerLimitSwitch(lowerLimitSwitch)
  {}

void LongPressedCommandState::init(const StateContext& stateContext) {
  this->direction = stateContext.direction;
}

StateTransition LongPressedCommandState::update(StateContext& stateContext) {
  Button& button = direction == Direction::UP ? 
    upBtn : 
    downBtn;

  // button released -> end of long-press
  if (!button.isPressed()) {
    motor.stop();

    Serial.write("long-pressed -> idle\n");
    return {
      commandStatePool.idle,
      {}
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
      } else {
        motor.down();
      }
      break;
  }


  return {
    this,
    stateContext
  };
}