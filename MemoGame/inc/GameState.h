#ifndef DEF_GAMESTATE
#define DEF_GAMESTATE

#include <SFML/Graphics.hpp>
#include "Card.h"
#include "Game.hpp"

struct cardId {
  Textures::ID id;
  int x, y;
};

class GameState
{
	public:
		GameState(Game&);
		enum State {PendingForFirstCard, PendingForSecondCard, GameOver};
		/**
		 * To be called in PendingForFirstCard state.
		 * Changes state to PendingForSecondCard.
		 */
		int flipFirstCard(cardId cid);
		/**
		 * To be called in PendingForSecondCard state.
		 * Changes state back to PendingForFirstCard, or to GameOver if all cards
		 * are succesfully paired.
		 */
		int flipSecondCard(cardId cid);
		/**
		 * To be called in GameOver state.
		 */
		void endGame();
		/**
		 * Returns game state.
		 */
		State getState();
		
	private:
		State state;
		Game game;
    cardId first;
    cardId second;
};

#endif
