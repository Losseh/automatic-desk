#include "command_state.h"
#include "long_pressed_command_state.h"
#include "Arduino.h"

LongPressedCommandState::LongPressedCommandState(CommandStatePool& commandStatePool, Components& components) : 
  commandStatePool(commandStatePool),
  components(components)
  {}

void LongPressedCommandState::init(const StateContext& stateContext) {
  direction = stateContext.direction;
  initiatingButton = direction == Direction::UP ? 
    &components.upBtn : 
    &components.downBtn;
}

StateTransition LongPressedCommandState::update(StateContext& stateContext) {
  // button released -> end of long-press
  if (!initiatingButton->isPressed()) {
    components.motor.stop();

    Serial.write("long-pressed -> idle\n");
    return {
      commandStatePool.idle,
      {}
    };
  }

  // TODO aszymanski: stop instant should happen also when current exceeds the limit
  switch (direction) {
    case Direction::UP:
      components.motor.up();
      break;

    case Direction::DOWN:
      if (components.lowerLimitSwitch.isPressed()) {
        components.motor.stopInstant();
      } else {
        components.motor.down();
      }
      break;
  }


  return {
    this,
    stateContext
  };
}