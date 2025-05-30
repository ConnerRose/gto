#pragma once

#include <cstdint>
#include <string>

#include "rank.hpp"
#include "suit.hpp"

namespace common {

/*
 * Bits 0-1: suit
 *
 * Bits 0-3: rank
 *
 * Bits 6-7: unused
 */
using card_t = uint8_t;

constexpr uint8_t NUM_CARDS = NUM_SUITS * NUM_RANKS;
constexpr uint8_t SUIT_MASK = 0b11;
constexpr uint8_t RANK_SHIFT = 2;

[[nodiscard]] constexpr card_t make_card(rank_t rank, suit_t suit) {
  return suit + (rank << RANK_SHIFT);
}

/*
 * `str` must be of length 2, str[0] = rank, str[1] = suit.
 */
[[nodiscard]] constexpr card_t card_from_string(const std::string& str) {
  if (str.size() != 2) {
    return NUM_CARDS;
  }
  return make_card(rank_from_char(str[0]), suit_from_char(str[1]));
}

[[nodiscard]] constexpr suit_t get_suit(card_t card) {
  return card & SUIT_MASK;
}

[[nodiscard]] constexpr rank_t get_rank(card_t card) {
  return card >> RANK_SHIFT;
}

[[nodiscard]] constexpr std::string card_to_string(card_t card) {
  return {{rank_to_char(get_rank(card)), suit_to_char(get_suit(card))}};
}

};  // namespace common
