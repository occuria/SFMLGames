#ifndef DEF_CARD
#define DEF_CARD

#include <SFML/Graphics.hpp>

class Card
{
	public:
		
		//Card(sf::RectangleShape s, sf::Texture b, sf::Texture f);
		sf::RectangleShape &getShape();
		sf::Texture &getBack();
		sf::Texture &getFront();
		void setShape(sf::RectangleShape r);
		void setBack(sf::Texture t);
		void setFront(sf::Texture t);
		void flipBack();
		void flipFront();

	private:

		sf::Texture back;
		sf::Texture front;
		sf::RectangleShape shape;
};

#endif
