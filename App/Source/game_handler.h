#include "player.h"
#include "renderer.h"

#include "the_game.pb.h"

class GameHandler {
private:
  Renderer renderer;
  Piles piles;
  Pile drawPile;
  std::vector<Cards> playersHands;
  std::vector<Player> players;
  int activePlayerIndex;

public:
  GameHandler();

  GameHandler(Piles piles);

  int startGame();

private:
  bool isGameOver();

  bool allCardsPlayed();

  bool activePlayerCanPlayNCards(int n);

  bool cardCanBePlayed(Card card);

  int minCardsToPlay();

  bool validateTurn(Piles possiblePilesAfterTurn);

  bool playerHasCards(int playerIndex, Cards cards);

  bool playerHasCard(int playerIndex, Card card);

  bool playedCorrectlyOnPile(Card card, Pile pile, bool increasing);

  void kickPlayer(int playerIndex);

  void updatePiles(Piles placedCards);

  void updatePlayersHand(Piles placedCards);

  void dealCardsToPlayer(int playerIndex);

  void advanceTurn();

  static bool canBePlayedOnPile(Card card, Pile pile, bool increasing);

  static bool inCorrectOrder(Pile pile, Pile playedCards, bool increasing);

  static Card getPilesTopCard(Pile pile);

  static Cards pilesToCards(Piles piles);

  static int maxHandSize(int playerCount);
};