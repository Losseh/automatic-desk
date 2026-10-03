#include "command_state.h"

#pragma once

struct CommandStatePool {
  CommandState* idle;
  CommandState* pressed;
  CommandState* shortPress;
  CommandState* longPress;
  CommandState* waitForRelease;
};