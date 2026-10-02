#include "command_state.h"

#pragma once

class IdleCommandState : public CommandState {
  StateTransition update();
};