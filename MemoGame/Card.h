#ifndef DEF_CARD
#define DEF_CARD

#include <SFML/Graphics.hpp>

class Card
{
	public:
		
		Card();
		Card(sf::RectangleShape s, int id);
		void flipOver(const sf::Texture &t);
		sf::RectangleShape &getShape();
		int getFid();
		bool getUpturned();
		//void setShape(sf::RectangleShape r);
		void setUpturned(bool u);

	private:

		sf::RectangleShape shape;
		int fid;
		bool upturned;

};

#endif
