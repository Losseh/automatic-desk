#include "led.h"
#include "Arduino.h"

#define LED_OFF 0x1
#define LED_ON  0x0

Led::Led(uint8_t pin): pin(pin) {}

void Led::begin() {
  pinMode(pin, OUTPUT);
  digitalWrite(pin, LED_OFF);
}

void Led::switchOn() {
  set(LED_ON);
}

void Led::switchOff() {
  set(LED_OFF);
}

void Led::set(uint8_t value) {
  digitalWrite(pin, value);
}
