#ifndef DEF_GAMESTATE
#define DEF_GAMESTATE

#include <SFML/Graphics.hpp>
#include "Card.h"

class GameState
{
	public:
		
	private:
		enum State {TurnStart, FirstCardFlip, SecondCardFlip, TurnEnd};
		State state;
		Card FirstCard;
		Card SecondCard;

};

#endif
