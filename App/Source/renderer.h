#include <string>
#include "the_game.pb.h"

#pragma once

class Renderer
{
public:
  void render(Piles piles, Cards hand);

public:
  static void pileToString(Pile pile);

  static void cardsToString(Cards cards);
};