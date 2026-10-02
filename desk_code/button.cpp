#import "button.h"
#import "Arduino.h"

Button::Button(uint8_t pin): pin(pin) {}

void Button::begin() {
  pinMode(pin, INPUT_PULLUP);
}

void Button::update() {
  bool reading = digitalRead(pin) == LOW;
  
  if (reading != previousState) {
    lastChangeTime = millis();
    previousState = reading;
  }

  if (millis() - lastChangeTime > 20) {
    stableState = reading;
  }
}

bool Button::isPressed() const {
  return stableState;
}