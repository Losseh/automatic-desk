#import "limit_switch.h"
#import "Arduino.h"

LimitSwitch::LimitSwitch(uint8_t pin): pin(pin) {}

void LimitSwitch::begin() {
  pinMode(pin, INPUT_PULLUP);
}

bool LimitSwitch::isPressed() const {
  return digitalRead(pin) == LOW;
}
