#include "stdint.h"

#pragma once

class Button {
public:
    explicit Button(uint8_t pin);
    
    void begin();

    void update();
    bool isPressed() const;

private:
    uint8_t pin;
    bool stableState;
    bool previousState;
    unsigned long lastChangeTime;
};