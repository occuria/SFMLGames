#ifndef DEF_GAMESTATE
#define DEF_GAMESTATE

#include <SFML/Graphics.hpp>
#include "Card.h"

class GameState
{
	public:
		GameState();
		
	private:
		enum State {TurnStart, FirstCardFlip, SecondCardFlip, TurnEnd};
		State state;
		Card firstCard;
		Card secondCard;

};

#endif
