#include "command_state.h"
#include "command_state_pool.h"
#include "button.h"

class WaitForReleaseState : public CommandState {
public:
  WaitForReleaseState(CommandStatePool& commandStatePool, Button& upBtn, Button& downBtn);
  void init(const StateContext& stateContext);
  StateTransition update(StateContext& stateContext);

private:
  CommandStatePool& commandStatePool;
  Button& upBtn;
  Button& downBtn;

  Button* initiatingBtn;
};