#include "command_state.h"
#include "command_state_pool.h"
#include "motor.h"
#include "limit_switch.h"
#include "direction.h"
#include "button.h"

#pragma once

class LongPressedCommandState : public CommandState {
public:
  LongPressedCommandState(CommandStatePool& commandStatePool, Button& upBtn, Button& downBtn, Motor& motor, LimitSwitch& lowerLimitSwitch);
  void init(const StateContext& stateContext);
  StateTransition update(StateContext& stateContext);

private:
  CommandStatePool& commandStatePool;
  Button& upBtn;
  Button& downBtn; 
  Motor& motor;
  LimitSwitch& lowerLimitSwitch;

  Direction direction;
};