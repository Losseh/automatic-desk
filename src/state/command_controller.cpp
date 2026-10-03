#include "command_controller.h"
#include "idle_command_state.h"
#include "pressed_command_state.h"
#include "short_pressed_command_state.h"
#include "long_pressed_command_state.h"
#include "wait_for_release_state.h"

CommandController::CommandController(Button& upBtn, Button& downBtn, Motor& motor, LimitSwitch& lowerLimitSwitch) : 
  upBtn(upBtn), 
  downBtn(downBtn), 
  motor(motor),
  lowerLimitSwitch(lowerLimitSwitch)
  {
    statePool.idle = new IdleCommandState(statePool, upBtn, downBtn);
    statePool.pressed = new PressedCommandState(statePool, upBtn, downBtn);
    statePool.shortPress = new ShortPressedCommandState(statePool, upBtn, downBtn, motor, lowerLimitSwitch);
    statePool.longPress = new LongPressedCommandState(statePool, upBtn, downBtn, motor, lowerLimitSwitch);
    statePool.waitForRelease = new WaitForReleaseState(statePool, upBtn, downBtn);

    current = statePool.idle;
    current->init(stateContext);
  }

void CommandController::update() {
  StateTransition transition = current->update(stateContext);

  if (transition.nextState != current) {
    current = transition.nextState;
    stateContext = transition.context;
    current->init(stateContext);
  }
}