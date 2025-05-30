#include "rank.hpp"

using namespace common;

int main() {
  constexpr rank_t INVALID_RANK = 13;
  static_assert(rank_to_char(TWO) == '2');
  static_assert(rank_to_char(THREE) == '3');
  static_assert(rank_to_char(FOUR) == '4');
  static_assert(rank_to_char(FIVE) == '5');
  static_assert(rank_to_char(SIX) == '6');
  static_assert(rank_to_char(SEVEN) == '7');
  static_assert(rank_to_char(EIGHT) == '8');
  static_assert(rank_to_char(NINE) == '9');
  static_assert(rank_to_char(TEN) == 'T');
  static_assert(rank_to_char(JACK) == 'J');
  static_assert(rank_to_char(QUEEN) == 'Q');
  static_assert(rank_to_char(KING) == 'K');
  static_assert(rank_to_char(ACE) == 'A');
  static_assert(rank_to_char(INVALID_RANK) == '?');

  static_assert(rank_from_char('2') == TWO);
  static_assert(rank_from_char('3') == THREE);
  static_assert(rank_from_char('4') == FOUR);
  static_assert(rank_from_char('5') == FIVE);
  static_assert(rank_from_char('6') == SIX);
  static_assert(rank_from_char('7') == SEVEN);
  static_assert(rank_from_char('8') == EIGHT);
  static_assert(rank_from_char('9') == NINE);
  static_assert(rank_from_char('t') == TEN);
  static_assert(rank_from_char('T') == TEN);
  static_assert(rank_from_char('j') == JACK);
  static_assert(rank_from_char('J') == JACK);
  static_assert(rank_from_char('q') == QUEEN);
  static_assert(rank_from_char('Q') == QUEEN);
  static_assert(rank_from_char('k') == KING);
  static_assert(rank_from_char('K') == KING);
  static_assert(rank_from_char('a') == ACE);
  static_assert(rank_from_char('A') == ACE);
  static_assert(rank_from_char('?') == INVALID_RANK);
  return 0;
}
