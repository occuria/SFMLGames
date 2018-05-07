#ifndef DEF_GAMESTATE
#define DEF_GAMESTATE

#include <SFML/Graphics.hpp>
#include "Card.h"

class GameState
{
	public:
		GameState();
		enum State {FirstCard, SecondCard, pending};
		State getState();
		std::vector<int> getCards();
		void flipFirstCard(int x, int y, int id);
		void flipSecondCard(int x, int y, int id);
		int endTurn();
		
	private:
		State state;
		int firstCard[3];
		int secondCard[3];
};

#endif
