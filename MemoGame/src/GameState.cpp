#include <iostream>
#include "../inc/GameState.h"

GameState::GameState()
{
  this->state = PendingForFirstCard;
}

/**
 * Return codes:
 * 0: cards must not be flipped back
 * 1: cards do not match, they must be flipped back
 * -1: error code
 */
int GameState::flipCardState(cardId cid)
{
  switch (this->state) {
    case PendingForFirstCard :
      this->first = cid;
      this->state = PendingForSecondCard;
      return 0;
    case PendingForSecondCard :
      this->second = cid;
      /* Checks wether card can be paired */
      if (this->first.id == this->second.id) {
        /* Cards are paired, they are left on the front side */
        this->state = PendingForFirstCard;
        return 0;
        /* Checks wether the game is over, and return 3 in this case */
      } else {
        this->state = PendingForFirstCard;
        return 1;
      }
    default :
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
