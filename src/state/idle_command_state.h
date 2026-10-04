#pragma once

#include "command_state.h"
#include "command_state_pool.h"
#include "button.h"
#include "../direction.h"

class IdleCommandState : public CommandState {
public:
  IdleCommandState(CommandStatePool& commandStatePool, Button& upBtn, Button& downBtn);
  StateTransition update(StateContext& stateContext);

private:
  CommandStatePool& commandStatePool;
  Button& upBtn;
  Button& downBtn;
};