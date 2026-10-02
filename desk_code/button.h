#include "stdint.h"

#pragma once

class Button {
public:
    explicit Button(uint8_t pin);
    void begin();
    bool isPressed() const;

private:
    uint8_t pin;
};