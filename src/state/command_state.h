#include "direction.h"

#pragma once

class CommandState;

struct StateContext {
  Direction direction;
};

struct StateTransition {
  CommandState* nextState;
  StateContext context;
};

class CommandState {
public:
  virtual ~CommandState() = default;
  virtual void init(const StateContext& stateContext) {}
  virtual StateTransition update(StateContext& stateContext) = 0;
};