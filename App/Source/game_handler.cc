#include "game_handler.h"
#include "renderer.h"
#include <chrono>
#include <iostream>
#include <thread>
#include "the_game.pb.h"

GameHandler::GameHandler()
{
  Renderer renderer;
  Piles piles;
  piles.mutable_firstone()->add_cards()->set_value(1);
  piles.mutable_secondone()->add_cards()->set_value(1);
  piles.mutable_firsthundred()->add_cards()->set_value(100);
  piles.mutable_secondhundred()->add_cards()->set_value(100);
  Pile drawPile;
  for (int i = 99; i > 8; i--)
  {
    drawPile.add_cards()->set_value(i);
  }
  Cards startingHand;
  for (int i = 2; i < 9; i++)
  {
    startingHand.add_cards()->set_value(i);
  }
  std::vector<Cards> playersHands;
  playersHands.push_back(startingHand);
  std::vector<Player> players;
  Player player;
  players.push_back(player);
  this->renderer = renderer;
  this->piles = piles;
  this->drawPile = drawPile;
  this->playersHands = playersHands;
  this->players = players;
  this->activePlayerIndex = 0;
}

GameHandler::GameHandler(Piles piles) : piles(piles) {}

int GameHandler::startGame()
{
  std::cout << "isGameOver: " << this->isGameOver() << std::endl;
  while (!this->isGameOver())
  {
    this->renderer.render(this->piles, this->playersHands[0]);
    std::this_thread::sleep_for(std::chrono::seconds(1));
    Player activePlayer = this->players[this->activePlayerIndex];
    Cards playerHand = this->playersHands[this->activePlayerIndex];
    Piles placedCards = activePlayer.playTurn(this->piles, playerHand);
    if (!validateTurn(placedCards))
    {
      this->kickPlayer(this->activePlayerIndex);
      continue; // TODO: Handle cleaning up the game after kicking a player
    }
    this->updatePiles(placedCards);
    this->updatePlayersHand(placedCards);
    this->dealCardsToPlayer(this->activePlayerIndex);
    this->advanceTurn();
  }
  this->renderer.render(this->piles, this->playersHands[0]);
  return 0;
}

bool GameHandler::isGameOver()
{
  if (this->allCardsPlayed())
  {
    return true;
  }
  else if (!this->activePlayerCanPlayNCards(this->minCardsToPlay()))
  {
    return true;
  }
  return false;
}

bool GameHandler::allCardsPlayed()
{
  if (this->drawPile.cards_size() > 0)
  {
    return false;
  }
  for (Cards playerHand : this->playersHands)
  {
    if (playerHand.cards_size() > 0)
    {
      return false;
    }
  }
  return true;
}

bool GameHandler::activePlayerCanPlayNCards(int n)
{
  int playableCardCount = 0;
  Cards activePlayersHand = playersHands[this->activePlayerIndex];
  for (Card card : activePlayersHand.cards())
  {
    if (this->cardCanBePlayed(card))
    {
      playableCardCount += 1;
      if (playableCardCount == n)
      {
        return true;
      }
    }
  }
  return false;
}

bool GameHandler::cardCanBePlayed(Card card)
{
  Piles piles = this->piles;
  if (GameHandler::canBePlayedOnPile(card, piles.firstone(), true))
  {
    return true;
  }
  else if (GameHandler::canBePlayedOnPile(card, piles.secondone(), true))
  {
    return true;
  }
  else if (GameHandler::canBePlayedOnPile(card, piles.firsthundred(),
                                          false))
  {
    return true;
  }
  else if (GameHandler::canBePlayedOnPile(card, piles.secondhundred(),
                                          false))
  {
    return true;
  }
  return false;
}

int GameHandler::minCardsToPlay()
{
  if (this->drawPile.cards_size() <= 0)
  {
    return 1;
  }
  return 2;
}

bool GameHandler::validateTurn(Piles playedCards)
{
  Cards cards = GameHandler::pilesToCards(playedCards);
  if (!this->playerHasCards(this->activePlayerIndex, cards))
  {
    return false;
  }
  if (!this->inCorrectOrder(this->piles.firstone(), playedCards.firstone(), true))
  {
    return false;
  }
  if (!this->inCorrectOrder(this->piles.secondone(), playedCards.secondone(), true))
  {
    return false;
  }
  if (!this->inCorrectOrder(this->piles.firsthundred(), playedCards.firsthundred(), false))
  {
    return false;
  }
  if (!this->inCorrectOrder(this->piles.secondhundred(), playedCards.secondhundred(), false))
  {
    return false;
  }
  return true;
}

bool GameHandler::playerHasCards(int playerIndex, Cards cards)
{
  for (Card card : cards.cards())
  {
    if (!this->playerHasCard(playerIndex, card))
    {
      return false;
    }
  }
  return true;
}

bool GameHandler::playerHasCard(int playerIndex, Card card)
{
  Cards playersHand = this->playersHands[playerIndex];
  for (Card playersCard : playersHand.cards())
  {
    if (card.value() == playersCard.value())
    {
      return true;
    }
  }
  return false;
}

bool GameHandler::playedCorrectlyOnPile(Card card, Pile pile,
                                        bool increasing)
{
  Card topCard = GameHandler::getPilesTopCard(pile);
  bool playedCardIncreasing = card.value() > topCard.value();
  return playedCardIncreasing == increasing;
}

void GameHandler::kickPlayer(int playerIndex)
{
  return; // TODO: add logic to kick out a player and add their cards to the
          // draw pile randomly
}

void GameHandler::updatePiles(Piles placedCards)
{
  for (Card card : placedCards.firstone().cards())
  {
    this->piles.mutable_firstone()->add_cards()->set_value(card.value());
  }
  for (Card card : placedCards.secondone().cards())
  {
    this->piles.mutable_secondone()->add_cards()->set_value(card.value());
  }
  for (Card card : placedCards.firsthundred().cards())
  {
    this->piles.mutable_firsthundred()->add_cards()->set_value(card.value());
  }
  for (Card card : placedCards.secondhundred().cards())
  {
    this->piles.mutable_secondhundred()->add_cards()->set_value(card.value());
  }
}

void GameHandler::updatePlayersHand(Piles placedCards)
{
  std::set<int> usedCards;
  Pile piles[4];
  piles[0] = placedCards.firstone();
  piles[1] = placedCards.secondone();
  piles[2] = placedCards.firsthundred();
  piles[3] = placedCards.secondhundred();
  for (Pile pile : piles)
  {
    for (Card card : pile.cards())
    {
      usedCards.insert(card.value());
    }
  }
  Cards newHand;
  for (Card card : this->playersHands[this->activePlayerIndex].cards())
  {
    if (usedCards.find(card.value()) == usedCards.end())
    {
      newHand.add_cards()->set_value(card.value());
    }
  }
  this->playersHands[this->activePlayerIndex] = newHand;
}

void GameHandler::dealCardsToPlayer(int playerIndex)
{
  Cards *playerHand = &this->playersHands[playerIndex];
  Renderer::cardsToString(*playerHand);
  Renderer::cardsToString(this->playersHands[this->activePlayerIndex]);
  int maxHandSize = GameHandler::maxHandSize(this->players.size());
  while (this->drawPile.cards_size() > 0 &&
         playerHand->cards_size() < maxHandSize)
  {
    Card drawnCard = GameHandler::getPilesTopCard(this->drawPile);
    playerHand->add_cards()->set_value(drawnCard.value());
    this->drawPile.mutable_cards()->RemoveLast();
  }
}

void GameHandler::advanceTurn()
{
  int playerCount = this->players.size();
  int startingIndex = this->activePlayerIndex;
  // only loop around once to not get into an infinite loop if game is over
  for (int i = startingIndex + 1 % playerCount; i != startingIndex;
       i = i + 1 % playerCount)
  {
    Cards playersHand = this->playersHands[i];
    if (playersHand.cards_size() > 0)
    {
      this->activePlayerIndex = i;
      return;
    }
  }
}

bool GameHandler::canBePlayedOnPile(Card card, Pile pile, bool increasing)
{
  int32_t topCardValue = GameHandler::getPilesTopCard(pile).value();
  if (increasing)
  {
    return topCardValue < card.value();
  }
  else
  {
    return topCardValue > card.value();
  }
}

bool GameHandler::inCorrectOrder(Pile pile, Pile playedCards, bool increasing)
{
  Card topCard = GameHandler::getPilesTopCard(pile);
  int previousCardValue = topCard.value();
  for (Card card : playedCards.cards())
  {
    if (increasing)
    {
      if (!(card.value() > previousCardValue || card.value() - 10 == previousCardValue))
      {
        return false;
      }
    }
    else
    {
      if (!(card.value() < previousCardValue || card.value() + 10 == previousCardValue))
      {
        return false;
      }
    }
    previousCardValue = card.value();
  }
  return true;
}

Card GameHandler::getPilesTopCard(Pile pile)
{
  return pile.cards(pile.cards_size() - 1);
}

Cards GameHandler::pilesToCards(Piles piles)
{
  Cards cards;
  std::vector<Pile> pileList;
  pileList.push_back(piles.firstone());
  pileList.push_back(piles.secondone());
  pileList.push_back(piles.firsthundred());
  pileList.push_back(piles.secondhundred());
  for (Pile pile : pileList)
  {
    for (Card card : pile.cards())
    {
      cards.add_cards()->set_value(card.value());
    }
  }
  return cards;
}

int GameHandler::maxHandSize(int playerCount)
{
  switch (playerCount)
  {
  case 1:
    return 8;
  case 2:
    return 7;
  case 3:
    return 6;
  case 4:
    return 6;
  }
  return 5;
}