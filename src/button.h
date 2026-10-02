#include "stdint.h"

#pragma once

enum ButtonId {
  UP, DOWN
};

class Button {
public:
    explicit Button(uint8_t pin);
    
    void begin();

    void update();
    bool isPressed() const;

private:
    uint8_t pin;
    bool stableState;
    bool lastReading;
    unsigned long lastChangeTime;
};