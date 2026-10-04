#include "position.h"

Position::Position() : position(0) {}

long Position::getPosition() {
  return position;
}

void Position::update(long impulses, Direction direction) {
  if (direction == Direction::UP) {
    position += impulses;
  } else {
    position -= impulses;
  }
}