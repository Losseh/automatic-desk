#include "stdint.h"

class Led {
public:
  explicit Led(uint8_t pin);
  void begin();
  void switchOn();
  void switchOff();
  void set(uint8_t value);

private:
  int pin;
};