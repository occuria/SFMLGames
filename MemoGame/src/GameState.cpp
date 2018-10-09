#include <iostream>
#include "../inc/GameState.h"

GameState::GameState(Game& game): game(game)
{
	this->state = PendingForFirstCard;
}

GameState::State GameState::getState()
{
	return this->state;
}

int GameState::flipFirstCard(cardId cid)
{
	if (this->state != PendingForFirstCard) {
    return -1;
	}
	this->first = cid;
	this->state = PendingForSecondCard;
	this->game.getBoard()[cid.x][cid.y].flipFront();
	return 0;
}

int GameState::flipSecondCard(cardId cid)
{
	if (this->state != PendingForSecondCard
	    || this->first.id <= Textures::FrontOffset
	    || this->second.id <= Textures::FrontOffset)
	{
		return -1;
	}
	this->second = cid;

	/* Checks if cards match and decides of the next state */
	if (first.id != second.id) {
    this->state = PendingForFirstCard;
    return 0;
  } else {
    this->state = GameOver;
    endGame();
    return 0;
  }
}

void GameState::endGame()
{
  std::cout << "Game over !" << std::endl;
}
