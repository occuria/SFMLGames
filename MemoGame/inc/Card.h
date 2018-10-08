#ifndef DEF_CARD
#define DEF_CARD

#include <SFML/Graphics.hpp>
#include "TextureHolder.hpp"
#include "BoardDimensions.hpp"

#define CARDBACK Textures::CardBack

class Card
{
	public:
	  /**
	   * Deault constructor, used to initialize GameState.
	   */
	  Card();
		/**
		 * Complete constructor.
		 */
		Card(boardDimensions bd, Textures::ID pairId);
		/**
		 * Flip the card on the front side, changes the shape texture.
		 */
		int flipFront();
		/**
		 * Flip the card on the front side, changes the shape texture.
		 * Uses the CARDBACK macro.
		 */
		int flipBack();
		/**
		 * Sets paired value to true.
		 */
		void pair();
		/**
		 * Sets paired value to false.
		 */
		void unpair();
		/**
		 * Returns the value of pairId.
		 */
		int getPairId();
		/**
		 * Returns the value of paired.
		 */
		bool isPaired();
		/**
		 * Returns the shape.
		 */
		sf::Sprite& getSprite();

	private:

		sf::Sprite s;
    Textures::ID pairId;
		bool isFlipped;

};

#endif
