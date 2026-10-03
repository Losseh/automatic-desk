#include "command_state.h"
#include "command_state_pool.h"
#include "components.h"

class CommandController {
public:
  CommandController(Components& components);
  void update();

private:
  Components& components;

  CommandStatePool statePool;
  CommandState* current;
  StateContext stateContext;
};