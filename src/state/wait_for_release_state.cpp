#include "command_state.h"
#include "wait_for_release_state.h"
#include "Arduino.h"

WaitForReleaseState::WaitForReleaseState(CommandStatePool& commandStatePool, Button& upBtn, Button& downBtn) : 
  commandStatePool(commandStatePool),
  upBtn(upBtn),
  downBtn(downBtn)
  {}

void WaitForReleaseState::init(const StateContext& stateContext) {
  initiatingBtn = stateContext.direction == Direction::UP ? &upBtn : &downBtn;
}

StateTransition WaitForReleaseState::update(StateContext& stateContext) {
  // initiating button released -> end of wait-for-release
  if (!initiatingBtn->isPressed()) {
    Serial.write("wait-for-release -> idle\n");
    return {
      commandStatePool.idle,
      {}
    };
  }

  return {
    this,
    stateContext
  };
}