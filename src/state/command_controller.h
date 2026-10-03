#include "command_state.h"
#include "button.h"
#include "motor.h"
#include "limit_switch.h"
#include "command_state_pool.h"

class CommandController {
public:
  CommandController(Button& upBtn, Button& downBtn, Motor& motor, LimitSwitch& lowerLimitSwitch);
  void update();

private:
  Button& upBtn;
  Button& downBtn;
  Motor& motor;
  LimitSwitch& lowerLimitSwitch;

  CommandStatePool statePool;
  CommandState* current;
  StateContext stateContext;
};