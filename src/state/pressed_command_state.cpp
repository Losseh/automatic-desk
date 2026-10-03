#include "command_state.h"
#include "pressed_command_state.h"
#include "Arduino.h"

PressedCommandState::PressedCommandState(CommandStatePool& commandStatePool, Button& upBtn, Button& downBtn) : 
  commandStatePool(commandStatePool),
  upBtn(upBtn),
  downBtn(downBtn)
  {}

void PressedCommandState::init(const StateContext& stateContext) {
  this->direction = stateContext.direction;
  pressedAt = millis();
}

StateTransition PressedCommandState::update(StateContext& stateContext) {
  Button& initiatingButton = direction == Direction::UP ? 
    upBtn : 
    downBtn;

  if (!initiatingButton.isPressed()) {
    Serial.write("pressed -> short-pressed\n");
    return {
      commandStatePool.shortPress,
      { direction }
    };
  }

  if (millis() - pressedAt >= longPressThresholdInMs) {
    Serial.write("pressed -> long-pressed\n");
    return {
      commandStatePool.longPress,
      { direction }
    };
  }

  return {
    this,
    { direction }
  };
}