#ifndef DEF_GAMESTATE
#define DEF_GAMESTATE

#include <SFML/Graphics.hpp>
#include "TextureHolder.hpp"

class Game;

struct cardId {
  Textures::ID id;
  sf::Vector2i pos;
};

class GameState
{
	public:
		enum State {PendingForFirstCard, PendingForSecondCard, Decision, GameOver};
		/**
		 * Default constructor to set the initial state.
		 */
		GameState();
		/**
		 * To be called in PendingForFirstCard or PendingForSecondCard state.
		 * Updates the state appropriately.
		 */
		int nextState(cardId cid);
		/**
		 * To be called in GameOver state.
		 */
		void endGame();
		/**
		 * Returns game state.
		 */
		State getState();
		/**
		 * Returns both card id.
		 */
    std::vector<sf::Vector2i> getCards();
		
	private:
		State state;
    cardId first;
    cardId second;
};

#endif
