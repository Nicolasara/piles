#include "the_game.pb.h"
#include <string>

#pragma once

class Renderer {
public:
  void render(Piles piles, Cards hand);

public:
  static void pileToString(Pile pile);

  static void cardsToString(Cards cards);
};