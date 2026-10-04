#include "direction.h"

class Position {
public:
  Position();

  long getPosition();
  void update(long impulses, Direction direction);

private:
  long position;
};