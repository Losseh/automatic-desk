#include "command_controller.h"
#include "idle_command_state.h"
#include "pressed_command_state.h"
#include "short_pressed_command_state.h"
#include "long_pressed_command_state.h"
#include "wait_for_release_state.h"

CommandController::CommandController(Components& components) : 
  components(components)
  {
    statePool.idle = new IdleCommandState(statePool, components.upBtn, components.upBtn);
    statePool.pressed = new PressedCommandState(statePool, components.upBtn, components.upBtn);
    statePool.shortPress = new ShortPressedCommandState(statePool, components);
    statePool.longPress = new LongPressedCommandState(statePool, components);
    statePool.waitForRelease = new WaitForReleaseState(
      statePool, components.upBtn, components.downBtn);

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