#ifndef DEF_CARD
#define DEF_CARD

#include <SFML/Graphics.hpp>

class Card
{
	public:
		
		Card();
		Card(sf::RectangleShape s, int id);
		int flipOver(const sf::Texture &t);
		int flipBack(const sf::Texture &t);
		sf::RectangleShape &getShape();
		int getFid();
		void pair();
		void unpair();
		bool isPaired();

	private:

		sf::RectangleShape shape;
		int fid;
		bool paired;

};

#endif
