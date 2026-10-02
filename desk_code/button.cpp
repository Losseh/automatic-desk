#import "button.h"
#import "Arduino.h"

Button::Button(uint8_t pin): pin(pin) {}

void Button::begin() {
  pinMode(pin, INPUT_PULLUP);
}

bool Button::isPressed() const {
  return digitalRead(pin) == LOW;
}