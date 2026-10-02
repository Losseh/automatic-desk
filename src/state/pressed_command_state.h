#include "command_state.h"
#include "button.h"

class PressedCommandState : public CommandState {
public:
  PressedCommandState();
  StateTransition update();
};