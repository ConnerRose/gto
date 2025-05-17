#include <cassert>

#include "deck.hpp"

int main() {
  card_t ace_hearts = make_card(HEARTS, ACE);
  assert(get_rank(ace_hearts) == ACE);
  assert(get_suit(ace_hearts) == HEARTS);
  return 0;
}
