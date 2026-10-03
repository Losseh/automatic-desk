#include "idle_command_state.h"
#include "Arduino.h"

IdleCommandState::IdleCommandState(CommandStatePool& commandStatePool, Button& upBtn, Button& downBtn) : 
  commandStatePool(commandStatePool), upBtn(upBtn), downBtn(downBtn)
  {}

StateTransition IdleCommandState::update(StateContext& stateContext) {
    if (upBtn.isPressed()) {
        Serial.write("idle -> pressed(up)\n");
        return {
            commandStatePool.pressed,
            { Direction::UP }
        };
    }

    if (downBtn.isPressed()) {
        Serial.write("idle -> pressed(down)\n");
        return {
            commandStatePool.pressed,
            { Direction::DOWN }
        };
    }

    // Serial.write("idle -> idle\n");
    return {
        this,
        {}
    };
}