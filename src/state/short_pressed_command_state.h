#pragma once

#include "command_state.h"
#include "command_state_pool.h"
#include "components.h"
#include "../direction.h"

class ShortPressedCommandState : public CommandState {
public:
  ShortPressedCommandState(CommandStatePool& commandStatePool, Components& components);
  void init(const StateContext& stateContext);
  StateTransition update(StateContext& stateContext);

private:
  CommandStatePool& commandStatePool;
  Components& components;

  Direction direction;
};