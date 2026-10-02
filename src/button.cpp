#include "button.h"
#include "Arduino.h"

Button::Button(uint8_t pin): pin(pin), stableState(stableState), lastReading(lastReading) {}

void Button::begin() {
  pinMode(pin, INPUT_PULLUP);
}

void Button::update() {
  bool reading = digitalRead(pin) == LOW;
  
  if (reading != lastReading) {
    lastChangeTime = millis();
    lastReading = reading;
  }

  if (millis() - lastChangeTime > 20) {
    stableState = reading;
  }
}

bool Button::isPressed() const {
  return stableState;
}