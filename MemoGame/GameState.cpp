#include <iostream>
#include "GameState.h"

GameState::GameState()
{
	state = FirstCard;
}

GameState::State GameState::getState()
{
	return state;
}

std::vector<int> GameState::getCards()
{
	std::vector<int> res;
	res.push_back(firstCard[0]);
	res.push_back(firstCard[1]);
	res.push_back(secondCard[0]);
	res.push_back(secondCard[1]);
	return res;
}

void GameState::flipFirstCard(int x, int y, int id)
{
	if (state != FirstCard) {
		std::cout << "Game must be in FirstCard state" << std::endl;
		return;
	}
	firstCard[0] = x;
	firstCard[1] = y;
	firstCard[2] = id;
	state = SecondCard;
}

void GameState::flipSecondCard(int x, int y, int id)
{
	if (state != SecondCard) {
		std::cout << "Game must be in SecondCard state" << std::endl;
		return;
	}
	if (x == firstCard[0] && y == firstCard[1]) {
		std::cout << "Can't flip over twice the same card in a turn" << std::endl;
		return;
	}
	secondCard[0] = x;
	secondCard[1] = y;
	secondCard[2] = id;
	state = pending;
}

int GameState::endTurn()
{
	int res;
	if (state != pending) {
		std::cout << "Game must be in pending state" << std::endl;
		return -1;
	}
	if (secondCard[2] == firstCard[2]) {
		res = 0;
	} else {
		res = 1;
	}
	state = FirstCard;
	return res;
}
