#pragma once

#include <array>
#include <cstddef>
#include <cstdint>
#include <string>

constexpr size_t NUM_SUITS = 4;
using suit_t = uint8_t;
constexpr suit_t HEARTS = 0;
constexpr suit_t SPADES = 1;
constexpr suit_t DIAMONDS = 2;
constexpr suit_t CLUBS = 3;

constexpr std::array<std::string, NUM_SUITS> SUIT_NAMES = {"hearts", "spades",
                                                           "diamonds", "clubs"};

constexpr size_t NUM_RANKS = 13;
using rank_t = uint8_t;
constexpr rank_t ACE = 0;
constexpr rank_t TWO = 1;
constexpr rank_t THREE = 2;
constexpr rank_t FOUR = 3;
constexpr rank_t FIVE = 4;
constexpr rank_t SIX = 5;
constexpr rank_t SEVEN = 6;
constexpr rank_t EIGHT = 7;
constexpr rank_t NINE = 8;
constexpr rank_t TEN = 9;
constexpr rank_t JACK = 10;
constexpr rank_t QUEEN = 11;
constexpr rank_t KING = 12;

constexpr std::array<std::string, NUM_RANKS> RANK_NAMES = {
    "ace",   "two",  "three", "four", "five",  "six",  "seven",
    "eight", "nine", "ten",   "jack", "queen", "king",
};

/*
 * Bits 0-1: suit
 *
 * Bits 2-5: rank
 *
 * Bits 6-7: unused
 */
using card_t = uint8_t;

inline suit_t get_suit(card_t card) {
  return card & 0b11;
}

inline rank_t get_rank(card_t card) {
  return card >> 2;
}

inline card_t make_card(suit_t suit, rank_t rank) {
  return suit | (rank << 2);
}
