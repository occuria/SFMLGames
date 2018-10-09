#include <iostream>
#include "../inc/GameState.h"

GameState::GameState()
{
  this->state = PendingForFirstCard;
}

/**
 * Return codes:
 * 0: flip the card on the front
 * 1: nothing, cards are paired
 * 2: flip both cards back, they are not paired
 * -1: error code
 */
int GameState::nextState(cardId cid)
{
  switch (this->state) {
    case PendingForFirstCard :
      this->first = cid;
      this->state = PendingForSecondCard;
      return 0;
    case PendingForSecondCard :
      this->second = cid;
      this->state = Decision;
      return 0;
      break;
    case Decision :
      /* Checks wether card can be paired */
      this->state = PendingForFirstCard;
      std::cout << "Decision : ";
      if (this->first.id == this->second.id) {
        std::cout << "Match" << std::endl;
        /* Paired */
        return 1;
      } else {
        std::cout << "Don'tMatch" << std::endl;
        /* Not paired */
        return 2;
      }
      break;
    case GameOver :
      return -1;
  }
	return -1;
}

void GameState::endGame()
{
  std::cout << "Game over !" << std::endl;
}

GameState::State GameState::getState()
{
	return this->state;
}

std::vector<sf::Vector2i> GameState::getCards()
{
  std::vector<sf::Vector2i> res;
  res.push_back(this->first.pos);
  res.push_back(this->second.pos);
	return res;
}
