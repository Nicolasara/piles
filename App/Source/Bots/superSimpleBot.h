#include "../the_game.pb.h"
#include "bot.h"

#pragma once

class SuperSimpleBot : public Bot {
  // SuperSimpleBot class that implements the Bot interface and plays the first
  // two cards in the player's hand on the first two piles.
public:
  Piles playTurn(Piles piles, Cards cards);
};
