#include "card.hpp"

using namespace common;

int main() {
  constexpr card_t ACE_HEARTS = make_card(ACE, HEARTS);
  static_assert(card_to_string(ACE_HEARTS) == "Ah");
  static_assert(card_from_string("Ah") == ACE_HEARTS);
  static_assert(card_from_string("AH") == ACE_HEARTS);
  static_assert(card_from_string("ah") == ACE_HEARTS);
  static_assert(card_from_string("aH") == ACE_HEARTS);
  return 0;
}
