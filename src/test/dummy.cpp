#include <cassert>

#include "dummy.hpp"

int main() {
  dummy thing{};
  assert(thing.field == 0);
  return 0;
}
