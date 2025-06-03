#pragma once

#include <bit>
#include <cstdint>
#include <initializer_list>

#include "card.hpp"
#include "suit.hpp"

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

[[nodiscard]] constexpr std::array<hand_t, NUM_SUITS> make_suit_masks() {
  std::array<hand_t, NUM_SUITS> suit_masks{0};
  for (suit_t suit = 0; suit < NUM_SUITS; ++suit) {
    for (rank_t rank = 0; rank < NUM_RANKS; ++rank) {
      suit_masks[suit] = add_card(suit_masks[suit], make_card(rank, suit));
    }
  }
  return suit_masks;
}

[[nodiscard]] constexpr std::array<hand_t, NUM_RANKS> make_rank_masks() {
  std::array<hand_t, NUM_RANKS> rank_masks{0};
  for (suit_t suit = 0; suit < NUM_SUITS; ++suit) {
    for (rank_t rank = 0; rank < NUM_RANKS; ++rank) {
      rank_masks[rank] = add_card(rank_masks[rank], make_card(rank, suit));
    }
  }
  return rank_masks;
}

constexpr std::array<hand_t, NUM_SUITS> SUIT_MASKS = make_suit_masks();
constexpr std::array<hand_t, NUM_RANKS> RANK_MASKS = make_rank_masks();

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

[[nodiscard]] constexpr int suit_count(hand_t hand, suit_t suit) {
  return std::popcount(hand & SUIT_MASKS[suit]);
}

[[nodiscard]] constexpr int rank_count(hand_t hand, rank_t rank) {
  return std::popcount(hand & RANK_MASKS[rank]);
}

};  // namespace common
