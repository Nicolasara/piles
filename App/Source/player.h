#include "the_game.pb.h"

#pragma once

class Player {
public:
  Piles playTurn(Piles piles, Cards cards);
};
