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
      if (this->first.id == this->second.id) {
        /* Paired */
        return 1;
      } else {
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
  res[0] = this->first.pos;
  res[1] = this->second.pos;
	return res;
}
