#include "suit.hpp"

using namespace common;

int main() {
  constexpr suit_t INVALID_SUIT = 4;
  static_assert(suit_to_char(CLUBS) == 'c');
  static_assert(suit_to_char(DIAMONDS) == 'd');
  static_assert(suit_to_char(HEARTS) == 'h');
  static_assert(suit_to_char(SPADES) == 's');
  static_assert(suit_to_char(INVALID_SUIT) == '?');

  static_assert(suit_from_char('c') == CLUBS);
  static_assert(suit_from_char('C') == CLUBS);
  static_assert(suit_from_char('d') == DIAMONDS);
  static_assert(suit_from_char('D') == DIAMONDS);
  static_assert(suit_from_char('h') == HEARTS);
  static_assert(suit_from_char('H') == HEARTS);
  static_assert(suit_from_char('s') == SPADES);
  static_assert(suit_from_char('S') == SPADES);
  static_assert(suit_from_char('?') == INVALID_SUIT);
  return 0;
}
