#pragma once

#include <bit>
#include <cstdint>

#include "hand.hpp"
#include "rank.hpp"
#include "suit.hpp"

namespace common {

using hand_category_t = uint8_t;
constexpr hand_category_t HIGH_CARD = 0;
constexpr hand_category_t ONE_PAIR = 1;
constexpr hand_category_t TWO_PAIR = 2;
constexpr hand_category_t THREE_OF_A_KIND = 3;
constexpr hand_category_t STRAIGHT = 4;
constexpr hand_category_t FLUSH = 5;
constexpr hand_category_t FULL_HOUSE = 6;
constexpr hand_category_t FOUR_OF_A_KIND = 7;
constexpr hand_category_t STRAIGHT_FLUSH = 8;

constexpr int HAND_SIZE = 5;
constexpr uint16_t STRAIGHT_MASK = 0b11111;

/*
 * Bitset type to represent the kickers for a hand.
 *
 * We know kickers to be unique, as otherwise they
 * would be included in determining the hand's category.
 */
using kicker_t = uint16_t;

struct hand_rank_t {
  hand_category_t category{};
  rank_t primary{};
  rank_t secondary{};
  kicker_t kickers{};
};

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

[[nodiscard]] constexpr bool is_flush(hand_t hand, suit_t suit) {
  return std::popcount(hand & SUIT_MASKS[suit]) >= HAND_SIZE;
}

[[nodiscard]] constexpr kicker_t get_kickers(hand_t hand,
                                             int num_kickers = HAND_SIZE) {
  kicker_t kickers{0};
  int count{0};
  for (rank_t i = 0; i < NUM_RANKS; ++i) {
    rank_t rank = ACE - i;
    if (std::popcount(hand & RANK_MASKS[rank]) > 0) {
      kickers |= (1 << rank);
      if (++count == num_kickers) {
        break;
      }
    }
  }
  return kickers;
}

/*
 * Note regarding the following functions:
 *
 * Each function assumes that the previous has already been
 * called, and that the hand does not fit any higher category.
 * E.g., a call to `handle_one_pair(hand)` assumes that `hand`
 * has already been verified to not be two pair or higher.
 */

[[nodiscard]] constexpr hand_rank_t handle_straight(hand_t hand) {
  // start with ace-high straight
  kicker_t mask = STRAIGHT_MASK << (ACE - SIX);
  kicker_t cards = get_kickers(hand, NUM_RANKS);
  for (rank_t rank = ACE; rank >= SIX; --rank, mask >>= 1) {
    if (std::popcount(static_cast<uint16_t>(cards & mask)) == HAND_SIZE) {
      return {
          .category = STRAIGHT,
          .primary = rank,
          .secondary = 0,
          .kickers = 0,
      };
    }
  }
  mask |= (1 << ACE);
  if (std::popcount(static_cast<uint16_t>(cards & mask)) == HAND_SIZE) {
    return {
        .category = STRAIGHT,
        .primary = FIVE,
        .secondary = 0,
        .kickers = 0,
    };
  }
  return {};
}

[[nodiscard]] constexpr hand_rank_t handle_straight_flush(hand_t hand) {
  for (suit_t suit = 0; suit < NUM_SUITS; ++suit) {
    if (!is_flush(hand, suit)) {
      continue;
    }
    if (auto hand_rank = handle_straight(hand & SUIT_MASKS[suit]);
        hand_rank.category == STRAIGHT) {
      return {
          .category = STRAIGHT_FLUSH,
          .primary = hand_rank.primary,
          .secondary = 0,
          .kickers = 0,
      };
    }
  }
  return {};
}

[[nodiscard]] constexpr hand_rank_t handle_four_of_a_kind(hand_t hand) {
  for (rank_t i = 0; i < NUM_RANKS; ++i) {
    rank_t rank = ACE - i;
    if (std::popcount(hand & RANK_MASKS[rank]) == 4) {
      return {
          .category = FOUR_OF_A_KIND,
          .primary = rank,
          .secondary = 0,
          .kickers = get_kickers(hand & ~RANK_MASKS[rank], 1),
      };
    }
  }
  return {};
}

[[nodiscard]] constexpr hand_rank_t handle_full_house(hand_t hand) {
  rank_t primary = NUM_RANKS;
  for (rank_t i = 0; i < NUM_RANKS; ++i) {
    rank_t rank = ACE - i;
    if (std::popcount(hand & RANK_MASKS[rank]) == 3) {
      primary = rank;
      break;
    }
  }
  if (primary == NUM_RANKS) {
    return {};
  }
  hand &= ~RANK_MASKS[primary];
  for (rank_t i = 0; i < NUM_RANKS; ++i) {
    rank_t rank = ACE - i;
    if (std::popcount(hand & RANK_MASKS[rank]) == 2) {
      return {
          .category = FULL_HOUSE,
          .primary = primary,
          .secondary = rank,
          .kickers = 0,
      };
    }
  }
  return {};
}

[[nodiscard]] constexpr hand_rank_t handle_flush(hand_t hand) {
  for (suit_t suit = 0; suit < NUM_SUITS; ++suit) {
    if (is_flush(hand, suit)) {
      return {
          .category = FLUSH,
          .primary = 0,
          .secondary = 0,
          .kickers = get_kickers(hand & SUIT_MASKS[suit]),
      };
    }
  }
  return {};
}

[[nodiscard]] constexpr hand_rank_t handle_three_of_a_kind(hand_t hand) {
  for (rank_t i = 0; i < NUM_RANKS; ++i) {
    rank_t rank = ACE - i;
    if (std::popcount(hand & RANK_MASKS[rank]) == 3) {
      return {
          .category = THREE_OF_A_KIND,
          .primary = rank,
          .secondary = 0,
          .kickers = get_kickers(hand & ~RANK_MASKS[rank], 2),
      };
    }
  }
  return {};
}

[[nodiscard]] constexpr hand_rank_t handle_two_pair(hand_t hand) {
  rank_t primary = NUM_RANKS;
  rank_t secondary = NUM_RANKS;
  for (rank_t i = 0; i < NUM_RANKS; ++i) {
    rank_t rank = ACE - i;
    if (std::popcount(hand & RANK_MASKS[rank]) == 2) {
      if (primary == NUM_RANKS) {
        primary = rank;
      } else {
        secondary = rank;
        return {
            .category = TWO_PAIR,
            .primary = primary,
            .secondary = secondary,
            .kickers = get_kickers(
                hand & ~RANK_MASKS[primary] & ~RANK_MASKS[secondary], 1),
        };
      }
    }
  }
  return {};
}

[[nodiscard]] constexpr hand_rank_t handle_one_pair(hand_t hand) {
  for (rank_t i = 0; i < NUM_RANKS; ++i) {
    rank_t rank = ACE - i;
    if (std::popcount(hand & RANK_MASKS[rank]) == 2) {
      return {
          .category = ONE_PAIR,
          .primary = rank,
          .secondary = 0,
          .kickers = get_kickers(hand & ~RANK_MASKS[rank], 3),
      };
    }
  }
  return {};
}

[[nodiscard]] constexpr hand_rank_t handle_high_card(hand_t hand) {
  return {.category = HIGH_CARD,
          .primary = 0,
          .secondary = 0,
          .kickers = get_kickers(hand)};
}

[[nodiscard]] constexpr hand_rank_t evaluate_hand(hand_t hand) {
  if (auto hand_rank = handle_straight_flush(hand);
      hand_rank.category == STRAIGHT_FLUSH) {
    return hand_rank;
  }
  if (auto hand_rank = handle_four_of_a_kind(hand);
      hand_rank.category == FOUR_OF_A_KIND) {
    return hand_rank;
  }
  if (auto hand_rank = handle_full_house(hand);
      hand_rank.category == FULL_HOUSE) {
    return hand_rank;
  }
  if (auto hand_rank = handle_flush(hand); hand_rank.category == FLUSH) {
    return hand_rank;
  }
  if (auto hand_rank = handle_straight(hand); hand_rank.category == STRAIGHT) {
    return hand_rank;
  }
  if (auto hand_rank = handle_three_of_a_kind(hand);
      hand_rank.category == THREE_OF_A_KIND) {
    return hand_rank;
  }
  if (auto hand_rank = handle_two_pair(hand); hand_rank.category == TWO_PAIR) {
    return hand_rank;
  }
  if (auto hand_rank = handle_one_pair(hand); hand_rank.category == ONE_PAIR) {
    return hand_rank;
  }
  return handle_high_card(hand);
}

};  // namespace common
