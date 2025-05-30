#pragma once

#include <array>
#include <cstdint>

namespace common {

using suit_t = uint8_t;
constexpr uint8_t NUM_SUITS = 4;
constexpr suit_t CLUBS = 0;
constexpr suit_t DIAMONDS = 1;
constexpr suit_t HEARTS = 2;
constexpr suit_t SPADES = 3;

constexpr std::array<char, NUM_SUITS> SUIT_CHARS = {'c', 'd', 'h', 's'};

/*
 * Returns '?' if `suit` is invalid.
 */
[[nodiscard]] constexpr char suit_to_char(suit_t suit) {
  return suit < NUM_SUITS ? SUIT_CHARS[suit] : '?';
}

/*
 * Returns `NUM_SUITS` if `c` is invalid.
 */
[[nodiscard]] constexpr suit_t suit_from_char(char c) {
  switch (c) {
    case 'c':
    case 'C':
      return CLUBS;
    case 'd':
    case 'D':
      return DIAMONDS;
    case 'h':
    case 'H':
      return HEARTS;
    case 's':
    case 'S':
      return SPADES;
    default:
      return NUM_SUITS;
  }
}

};  // namespace common
