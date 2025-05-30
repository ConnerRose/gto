#include <cassert>

#include "card.hpp"
#include "hand.hpp"
#include "rank.hpp"
#include "suit.hpp"

using namespace common;

constexpr hand_t TEN_HEARTS = make_card(TEN, HEARTS);
constexpr hand_t JACK_HEARTS = make_card(JACK, HEARTS);
constexpr hand_t QUEEN_HEARTS = make_card(QUEEN, HEARTS);
constexpr hand_t KING_HEARTS = make_card(KING, HEARTS);
constexpr hand_t ACE_HEARTS = make_card(ACE, HEARTS);

int main() {
  hand_t hand1{0};
  assert(hand_size(hand1) == 0);
  hand1 = add_card(hand1, make_card(ACE, HEARTS));
  assert(hand_size(hand1) == 1);
  assert(hand_contains(hand1, make_card(ACE, HEARTS)));
  hand1 = remove_card(hand1, make_card(ACE, HEARTS));
  assert(hand_size(hand1) == 0);

  hand_t hand2 = make_hand(
      {TEN_HEARTS, JACK_HEARTS, QUEEN_HEARTS, KING_HEARTS, ACE_HEARTS});
  assert(hand_size(hand2) == 5);
  assert(hand_contains(hand2, TEN_HEARTS));
  assert(hand_contains(hand2, JACK_HEARTS));
  assert(hand_contains(hand2, QUEEN_HEARTS));
  assert(hand_contains(hand2, KING_HEARTS));
  assert(hand_contains(hand2, ACE_HEARTS));
  return 0;
}
