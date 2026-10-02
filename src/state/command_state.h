#include "button.h"

#pragma once

struct StateContext {
  Button& button;
  unsigned long startedAt;
};

struct StateTransition {
  CommandState* nextState;
  StateContext context;
};

class CommandState {
public:
  virtual ~CommandState() = default;
  virtual StateTransition update() = 0;
};