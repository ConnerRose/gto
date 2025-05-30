#include <algorithm>
#include <cassert>
#include <random>
#include <vector>

#include "evaluate.hpp"
#include "rank.hpp"
#include "suit.hpp"

using namespace common;

constexpr hand_t SUIT_MASK =
    0b0001000100010001000100010001000100010001000100010001;
constexpr hand_t RANK_MASK = 0b1111;

// constexpr card_t TWO_CLUBS = make_card(TWO, CLUBS);
// constexpr card_t THREE_CLUBS = make_card(THREE, CLUBS);
constexpr card_t FOUR_CLUBS = make_card(FOUR, CLUBS);
constexpr card_t FIVE_CLUBS = make_card(FIVE, CLUBS);
constexpr card_t SIX_CLUBS = make_card(SIX, CLUBS);
constexpr card_t SEVEN_CLUBS = make_card(SEVEN, CLUBS);
constexpr card_t EIGHT_CLUBS = make_card(EIGHT, CLUBS);
constexpr card_t NINE_CLUBS = make_card(NINE, CLUBS);
constexpr card_t TEN_CLUBS = make_card(TEN, CLUBS);
constexpr card_t JACK_CLUBS = make_card(JACK, CLUBS);
constexpr card_t QUEEN_CLUBS = make_card(QUEEN, CLUBS);
// constexpr card_t KING_CLUBS = make_card(KING, CLUBS);
// constexpr card_t ACE_CLUBS = make_card(ACE, CLUBS);

// constexpr card_t TWO_DIAMONDS = make_card(TWO, DIAMONDS);
constexpr card_t THREE_DIAMONDS = make_card(THREE, DIAMONDS);
constexpr card_t FOUR_DIAMONDS = make_card(FOUR, DIAMONDS);
constexpr card_t FIVE_DIAMONDS = make_card(FIVE, DIAMONDS);
constexpr card_t SIX_DIAMONDS = make_card(SIX, DIAMONDS);
constexpr card_t SEVEN_DIAMONDS = make_card(SEVEN, DIAMONDS);
constexpr card_t EIGHT_DIAMONDS = make_card(EIGHT, DIAMONDS);
constexpr card_t NINE_DIAMONDS = make_card(NINE, DIAMONDS);
constexpr card_t TEN_DIAMONDS = make_card(TEN, DIAMONDS);
constexpr card_t JACK_DIAMONDS = make_card(JACK, DIAMONDS);
// constexpr card_t QUEEN_DIAMONDS = make_card(QUEEN, DIAMONDS);
// constexpr card_t KING_DIAMONDS = make_card(KING, DIAMONDS);
// constexpr card_t ACE_DIAMONDS = make_card(ACE, DIAMONDS);

constexpr card_t TWO_HEARTS = make_card(TWO, HEARTS);
constexpr card_t THREE_HEARTS = make_card(THREE, HEARTS);
constexpr card_t FOUR_HEARTS = make_card(FOUR, HEARTS);
constexpr card_t FIVE_HEARTS = make_card(FIVE, HEARTS);
constexpr card_t SIX_HEARTS = make_card(SIX, HEARTS);
constexpr card_t SEVEN_HEARTS = make_card(SEVEN, HEARTS);
constexpr card_t EIGHT_HEARTS = make_card(EIGHT, HEARTS);
constexpr card_t NINE_HEARTS = make_card(NINE, HEARTS);
constexpr card_t TEN_HEARTS = make_card(TEN, HEARTS);
constexpr card_t JACK_HEARTS = make_card(JACK, HEARTS);
constexpr card_t QUEEN_HEARTS = make_card(QUEEN, HEARTS);
constexpr card_t KING_HEARTS = make_card(KING, HEARTS);
constexpr card_t ACE_HEARTS = make_card(ACE, HEARTS);

constexpr card_t TWO_SPADES = make_card(TWO, SPADES);
constexpr card_t THREE_SPADES = make_card(THREE, SPADES);
constexpr card_t FOUR_SPADES = make_card(FOUR, SPADES);
constexpr card_t FIVE_SPADES = make_card(FIVE, SPADES);
constexpr card_t SIX_SPADES = make_card(SIX, SPADES);
constexpr card_t SEVEN_SPADES = make_card(SEVEN, SPADES);
constexpr card_t EIGHT_SPADES = make_card(EIGHT, SPADES);
constexpr card_t NINE_SPADES = make_card(NINE, SPADES);
constexpr card_t TEN_SPADES = make_card(TEN, SPADES);
constexpr card_t JACK_SPADES = make_card(JACK, SPADES);
constexpr card_t QUEEN_SPADES = make_card(QUEEN, SPADES);
constexpr card_t KING_SPADES = make_card(KING, SPADES);
constexpr card_t ACE_SPADES = make_card(ACE, SPADES);

std::random_device rd;
std::mt19937 g(rd());

void test_straight_flush() {
  std::vector<std::vector<card_t>> test_hands = {
      {TEN_HEARTS, JACK_HEARTS, QUEEN_HEARTS, KING_HEARTS, ACE_HEARTS},
      {NINE_SPADES, TEN_SPADES, JACK_SPADES, QUEEN_SPADES, KING_SPADES},
      {EIGHT_CLUBS, NINE_CLUBS, TEN_CLUBS, JACK_CLUBS, QUEEN_CLUBS},
      {SEVEN_DIAMONDS, EIGHT_DIAMONDS, NINE_DIAMONDS, TEN_DIAMONDS,
       JACK_DIAMONDS},
      {SIX_HEARTS, SEVEN_HEARTS, EIGHT_HEARTS, NINE_HEARTS, TEN_HEARTS},
      {FIVE_SPADES, SIX_SPADES, SEVEN_SPADES, EIGHT_SPADES, NINE_SPADES},
      {FOUR_CLUBS, FIVE_CLUBS, SIX_CLUBS, SEVEN_CLUBS, EIGHT_CLUBS},
      {THREE_DIAMONDS, FOUR_DIAMONDS, FIVE_DIAMONDS, SIX_DIAMONDS,
       SEVEN_DIAMONDS},
      {TWO_HEARTS, THREE_HEARTS, FOUR_HEARTS, FIVE_HEARTS, SIX_HEARTS},
      {ACE_SPADES, TWO_SPADES, THREE_SPADES, FOUR_SPADES, FIVE_SPADES},
  };

  std::vector<rank_t> expected_primaries = {ACE,  KING,  QUEEN, JACK, TEN,
                                            NINE, EIGHT, SEVEN, SIX,  SIX};

  for (size_t i = 0; i < test_hands.size(); ++i) {
    hand_t hand = 0;
    std::shuffle(test_hands[i].begin(), test_hands[i].end(), g);
    for (card_t c : test_hands[i]) {
      hand = add_card(hand, c);
    }
    hand_rank_t rank = evaluate_hand(hand);
    assert(rank.category == STRAIGHT_FLUSH);
    assert(rank.primary == expected_primaries[i]);
    assert(rank.secondary == 0);
    assert(rank.kickers == 0);
  }
}

void test_four_of_a_kind() {
  // Four 7s and a King kicker
  auto hand = make_hand({
      make_card(SEVEN, CLUBS),
      make_card(SEVEN, DIAMONDS),
      make_card(SEVEN, HEARTS),
      make_card(SEVEN, SPADES),
      make_card(KING, HEARTS),
  });
  auto rank = evaluate_hand(hand);
  assert(rank.category == FOUR_OF_A_KIND);
  assert(rank.primary == SEVEN);
  assert(rank.kickers & (1 << KING));
}

void test_full_house() {
  // Three 5s and two Kings
  auto hand = make_hand({
      make_card(FIVE, HEARTS),
      make_card(FIVE, SPADES),
      make_card(FIVE, CLUBS),
      make_card(KING, DIAMONDS),
      make_card(KING, CLUBS),
  });
  auto rank = evaluate_hand(hand);
  assert(rank.category == FULL_HOUSE);
  assert(rank.primary == FIVE);
  assert(rank.secondary == KING);
}

void test_flush() {
  // Flush in hearts
  auto hand = make_hand({
      make_card(TWO, HEARTS),
      make_card(SIX, HEARTS),
      make_card(EIGHT, HEARTS),
      make_card(JACK, HEARTS),
      make_card(KING, HEARTS),
  });
  auto rank = evaluate_hand(hand);
  assert(rank.category == FLUSH);
  assert(rank.kickers & (1 << KING));
  assert(std::popcount(rank.kickers) == 5);
}

void test_straight() {
  // 4-5-6-7-8 mixed suits
  auto hand = make_hand({
      make_card(FOUR, HEARTS),
      make_card(FIVE, CLUBS),
      make_card(SIX, DIAMONDS),
      make_card(SEVEN, SPADES),
      make_card(EIGHT, HEARTS),
  });
  auto rank = evaluate_hand(hand);
  assert(rank.category == STRAIGHT);
  assert(rank.primary == EIGHT);
}

void test_three_of_a_kind() {
  // Three 9s and two kickers
  auto hand = make_hand({
      make_card(NINE, CLUBS),
      make_card(NINE, DIAMONDS),
      make_card(NINE, HEARTS),
      make_card(QUEEN, CLUBS),
      make_card(TWO, DIAMONDS),
  });
  auto rank = evaluate_hand(hand);
  assert(rank.category == THREE_OF_A_KIND);
  assert(rank.primary == NINE);
  assert(std::popcount(rank.kickers) == 2);
  assert(rank.kickers & (1 << QUEEN));
  assert(rank.kickers & (1 << TWO));
}

void test_two_pair() {
  // Two 3s, two Kings, one Ace
  auto hand = make_hand({
      make_card(THREE, HEARTS),
      make_card(THREE, CLUBS),
      make_card(KING, SPADES),
      make_card(KING, DIAMONDS),
      make_card(ACE, CLUBS),
  });
  auto rank = evaluate_hand(hand);
  assert(rank.category == TWO_PAIR);
  assert(rank.primary == KING);
  assert(rank.secondary == THREE);
  assert(rank.kickers & (1 << ACE));
}

void test_one_pair() {
  // Two Queens and three other cards
  auto hand = make_hand({
      make_card(QUEEN, HEARTS),
      make_card(QUEEN, CLUBS),
      make_card(FOUR, DIAMONDS),
      make_card(SEVEN, SPADES),
      make_card(KING, CLUBS),
  });
  auto rank = evaluate_hand(hand);
  assert(rank.category == ONE_PAIR);
  assert(rank.primary == QUEEN);
  assert(std::popcount(rank.kickers) == 3);
  assert(rank.kickers & (1 << KING));
  assert(rank.kickers & (1 << SEVEN));
  assert(rank.kickers & (1 << FOUR));
}

void test_high_card() {
  // A-9-6-3-2 offsuit
  auto hand = make_hand({
      make_card(ACE, SPADES),
      make_card(NINE, HEARTS),
      make_card(SIX, DIAMONDS),
      make_card(THREE, CLUBS),
      make_card(TWO, SPADES),
  });
  auto rank = evaluate_hand(hand);
  assert(rank.category == HIGH_CARD);
  assert(std::popcount(rank.kickers) == 5);
  assert(rank.kickers & (1 << ACE));
  assert(rank.kickers & (1 << NINE));
}

int main() {
  for (suit_t suit = 0; suit < NUM_SUITS; ++suit) {
    assert(SUIT_MASKS[suit] == SUIT_MASK << suit);
  }
  for (rank_t rank = 0; rank < NUM_RANKS; ++rank) {
    assert(RANK_MASKS[rank] == RANK_MASK << (NUM_SUITS * rank));
  }
  test_straight_flush();
  test_four_of_a_kind();
  test_full_house();
  test_flush();
  test_straight();
  test_three_of_a_kind();
  test_two_pair();
  test_one_pair();
  test_high_card();
  return 0;
}
