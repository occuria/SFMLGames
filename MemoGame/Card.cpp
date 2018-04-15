#include "Card.h"

/*
Card::Card(sf::RectangleShape r, sf::Texture b, sf::Texture f):
	back(b),
	front(f),
	shape(r)
{
}
*/

sf::RectangleShape Card::getShape()
{
	return shape;
}

sf::Texture Card::getBack()
{
	return back;
}

sf::Texture Card::getFront()
{
	return front;
}

void Card::setShape(sf::RectangleShape r)
{
	shape = r;
}

void Card::setBack(sf::Texture t)
{
	back = t;
}

void Card::setFront(sf::Texture t)
{
	front = t;
}

void Card::flipBack()
{
	shape.setTexture(NULL);
	sf::Texture t = back;
	shape.setTexture(&t);
}

void Card::flipFront()
{
	shape.setTexture(NULL);
	sf::Texture t = front;
	shape.setTexture(&t);
}
