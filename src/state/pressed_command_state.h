#include "command_state.h"
#include "button.h"
#include "command_state_pool.h"

class PressedCommandState : public CommandState {
public:
  PressedCommandState(CommandStatePool& commandStatePool, Button& upBtn, Button& downBtn);
  void init(const StateContext& stateContext);
  StateTransition update(StateContext& stateContext);

private:
  CommandStatePool& commandStatePool;
  Button& upBtn;
  Button& downBtn;

  Direction direction;
  unsigned long pressedAt = 0;
  const unsigned long longPressThresholdInMs = 500; 
};