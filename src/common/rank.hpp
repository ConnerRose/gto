#pragma once

#include <array>
#include <cstdint>

namespace common {

using rank_t = uint8_t;
constexpr uint8_t NUM_RANKS = 13;
constexpr rank_t TWO = 0;
constexpr rank_t THREE = 1;
constexpr rank_t FOUR = 2;
constexpr rank_t FIVE = 3;
constexpr rank_t SIX = 4;
constexpr rank_t SEVEN = 5;
constexpr rank_t EIGHT = 6;
constexpr rank_t NINE = 7;
constexpr rank_t TEN = 8;
constexpr rank_t JACK = 9;
constexpr rank_t QUEEN = 10;
constexpr rank_t KING = 11;
constexpr rank_t ACE = 12;

constexpr std::array<char, NUM_RANKS> RANK_CHARS = {
    '2', '3', '4', '5', '6', '7', '8', '9', 'T', 'J', 'Q', 'K', 'A',
};

/*
 * Returns `?` if `rank` is invalid.
 */
[[nodiscard]] constexpr char rank_to_char(rank_t rank) {
  return rank < NUM_RANKS ? RANK_CHARS[rank] : '?';
}

/*
 * Returns `NUM_RANKS` if `c` is invalid.
 */
[[nodiscard]] constexpr rank_t rank_from_char(char c) {
  switch (c) {
    case '2':
      return TWO;
    case '3':
      return THREE;
    case '4':
      return FOUR;
    case '5':
      return FIVE;
    case '6':
      return SIX;
    case '7':
      return SEVEN;
    case '8':
      return EIGHT;
    case '9':
      return NINE;
    case 't':
    case 'T':
      return TEN;
    case 'j':
    case 'J':
      return JACK;
    case 'q':
    case 'Q':
      return QUEEN;
    case 'k':
    case 'K':
      return KING;
    case 'a':
    case 'A':
      return ACE;
    default:
      return NUM_RANKS;
  }
}

};  // namespace common
