#include "the_game.pb.cc"
#include <gtest/gtest.h>

#define private public
#include "Bots/superSimpleBot.cc"
#include "Core/Core.h"
#include "game_handler.cc"
#include "renderer.cc"

class GameHandlerTests : public ::testing::Test {
protected:
  GameHandler gameHandler;
  Pile emptyPile;
  Pile singleCardPile;
  Pile fourCardPile;

  void SetUp() override {
    gameHandler = GameHandler();
    setUpPiles();
  }

  void setUpPiles() {
    // Initialize the empty pile
    emptyPile = Pile();

    // Initialize the singleCardPile with 1 card
    singleCardPile.add_cards()->set_value(42);

    // Initialize the fourCardPile with 4 cards
    fourCardPile.add_cards()->set_value(5);
    fourCardPile.add_cards()->set_value(10);
    fourCardPile.add_cards()->set_value(15);
    fourCardPile.add_cards()->set_value(20);
  }

  void TearDown() override {
    // Clean up any resources used in the tests
  }
};

TEST_F(GameHandlerTests, StartGameTest) {
  // Start the game
  int result = gameHandler.startGame();

  // Check if the game started successfully
  EXPECT_EQ(result, 0);
}

TEST_F(GameHandlerTests, GetPilesTopCardTestSingleCardInvalid) {
  EXPECT_THROW(GameHandler::getPilesTopCard(emptyPile), std::runtime_error);
}

TEST_F(GameHandlerTests, GetPilesTopCardTestSingleCard) {
  Card singleTopCard = GameHandler::getPilesTopCard(singleCardPile);
  EXPECT_EQ(42, singleTopCard.value());
}

TEST_F(GameHandlerTests, GetPilesTopCardTestMultipleCards) {
  // Get the top card
  Card topCard = GameHandler::getPilesTopCard(fourCardPile);

  // Assert that the top card has the expected value (the last card added)
  EXPECT_EQ(20, topCard.value());
}

TEST_F(GameHandlerTests, GetPilesTopCardTestEmptyPile) {
  // Attempt to get the top card from the empty pile and expect a runtime error
  EXPECT_THROW(GameHandler::getPilesTopCard(emptyPile), std::runtime_error);
}