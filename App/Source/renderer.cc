#include "renderer.h"
#include <iostream>
#include <sstream>
#include <string>
#include <cmath>
#include "the_game.pb.h"

void Renderer::render(Piles piles, Cards hand)
{
  Renderer::pileToString(piles.firstone());
  Renderer::pileToString(piles.secondone());
  Renderer::pileToString(piles.firsthundred());
  Renderer::pileToString(piles.secondhundred());
  Renderer::cardsToString(hand);
}

void Renderer::pileToString(Pile pile)
{
  std::string topRow;
  for (int i = 0; i < pile.cards_size(); i++)
  {
    topRow.append(" __");
  }
  std::cout << topRow << "__ " << std::endl;

  for (int i = 0; i < 3; i++)
  {
    std::string row;
    char cardChar;
    for (Card card : pile.cards())
    {
      if (card.value() >= std::pow(10, i))
      {
        cardChar = std::to_string(card.value())[i];
      }
      else
      {
        cardChar = ' ';
      }
      std::stringstream ss;
      ss << "|" << cardChar << " ";
      row.append(ss.str());
    }

    std::cout << row << "  |" << std::endl;
  }

  std::string bottomRow;
  for (int i = 0; i < pile.cards_size(); i++)
  {
    bottomRow.append("|__");
  }
  std::cout << bottomRow << "__|" << std::endl;
}

void Renderer::cardsToString(Cards cards)
{
  std::string topRow;
  for (int i = 0; i < cards.cards_size(); i++)
  {
    topRow.append(" __");
  }
  std::cout << topRow << "__ " << std::endl;

  for (int i = 0; i < 3; i++)
  {
    std::string row;
    char cardChar;
    for (Card card : cards.cards())
    {
      if (card.value() >= std::pow(10, i))
      {
        cardChar = std::to_string(card.value())[i];
      }
      else
      {
        cardChar = ' ';
      }
      std::stringstream ss;
      ss << "|" << cardChar << " ";
      row.append(ss.str());
    }

    std::cout << row << "  |" << std::endl;
  }

  std::string bottomRow;
  for (int i = 0; i < cards.cards_size(); i++)
  {
    bottomRow.append("|__");
  }
  std::cout << bottomRow << "__|" << std::endl;
}

/*

   __ __ __ ____
  |1 |9 |9 |9   |
  |0 |9 |7 |4   |
  |0 |  |  |    |
  |__|__|__|____|




 */