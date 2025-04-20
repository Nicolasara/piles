#include "superSimpleBot.h"
#include "../the_game.pb.h"

Piles SuperSimpleBot::playTurn(Piles piles, Cards cards) {
  int32_t firstCardValue = cards.cards(0).value();
  int32_t secondCardValue = cards.cards(1).value();
  Piles placedCards;
  placedCards.mutable_firstone()->add_cards()->set_value(firstCardValue);
  placedCards.mutable_secondone()->add_cards()->set_value(secondCardValue);
  return placedCards;
}