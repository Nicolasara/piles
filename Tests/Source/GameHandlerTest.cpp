#include "the_game.pb.cc"
#include <gtest/gtest.h>

#define private public
#include "Core/Core.h"
#include "game_handler.cc"
#include "player.cc"
#include "renderer.cc"

TEST(GameHandlerTests, GetPilesTopCardTestSingleCard) {
  // Test with a single card pile
  Pile singleCardPile;
  singleCardPile.add_cards()->set_value(42);

  Card singleTopCard = GameHandler::getPilesTopCard(singleCardPile);
  EXPECT_EQ(42, singleTopCard.value());
}

TEST(GameHandlerTests, GetPilesTopCardTestMultipleCards) {
  // Create a pile with multiple cards
  Pile pile;
  pile.add_cards()->set_value(5);
  pile.add_cards()->set_value(10);
  pile.add_cards()->set_value(15);
  pile.add_cards()->set_value(20);

  // Get the top card
  Card topCard = GameHandler::getPilesTopCard(pile);

  // Assert that the top card has the expected value (the last card added)
  EXPECT_EQ(20, topCard.value());
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}