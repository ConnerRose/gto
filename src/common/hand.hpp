#pragma once

#include <bit>
#include <cstdint>
#include <initializer_list>

#include "card.hpp"

namespace common {

/*
 * A hand is represented as a bitset of the cards.
 *
 * E.g., if the ace of hearts is contained in the
 * hand, then bit 50 (12 * 4 + 2) will be set to high.
 */
using hand_t = uint64_t;
constexpr hand_t EMPTY_HAND = 0;

[[nodiscard]] constexpr hand_t add_card(hand_t hand, card_t card) {
  return hand | (1ULL << card);
}

[[nodiscard]] constexpr hand_t remove_card(hand_t hand, card_t card) {
  return hand & ~(1ULL << card);
}

[[nodiscard]] constexpr hand_t make_hand(std::initializer_list<card_t> cards) {
  hand_t hand{EMPTY_HAND};
  for (card_t card : cards) {
    hand = add_card(hand, card);
  }
  return hand;
}

[[nodiscard]] constexpr bool hand_contains(hand_t hand, card_t card) {
  return static_cast<bool>(hand & (1ULL << card));
}

[[nodiscard]] constexpr int hand_size(hand_t hand) {
  return std::popcount(hand);
}

};  // namespace common
