#include "command_state.h"
#include "short_pressed_command_state.h"
#include "Arduino.h"

ShortPressedCommandState::ShortPressedCommandState(CommandStatePool& commandStatePool, Components& components) : 
  commandStatePool(commandStatePool),
  components(components)
  {}

void ShortPressedCommandState::init(const StateContext& stateContext) {
  this->direction = stateContext.direction;
}

StateTransition ShortPressedCommandState::update(StateContext& stateContext) {
  // any button pressed -> end of short-press
  bool upPressed = components.upBtn.isPressed();
  if (upPressed || components.downBtn.isPressed()) {
    components.motor.stop();

    Serial.write("short-pressed -> wait-for-release\n");
    return {
      commandStatePool.waitForRelease,
      { upPressed ? Direction::UP : Direction::DOWN }
    };
  }

  // TODO aszymanski: stop instant should happen also when current exceeds the limit
  switch (stateContext.direction) {
    case Direction::UP:
      components.motor.up();
      break;

    case Direction::DOWN:
      if (components.lowerLimitSwitch.isPressed()) {
        components.motor.stopInstant();
        return {
          commandStatePool.idle,
          {}
        };
      } else {
        components.motor.down();
      }
      break;

    return {
      this,
      stateContext
    };
  }


  return {
    this,
    stateContext
  };
}