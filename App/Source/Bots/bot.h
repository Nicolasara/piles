#include "../the_game.pb.h"

#pragma once

class Bot {
public:
  virtual ~Bot() = default; // Virtual destructor for proper cleanup
  virtual Piles playTurn(Piles piles, Cards cards) = 0; // Pure virtual function
};