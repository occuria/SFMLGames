#include "Card.h"

sf::RectangleShape &Card::getShape()
{
	return shape;
}

sf::Texture &Card::getBack()
{
	return back;
}

sf::Texture &Card::getFront()
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
	sf::Texture t = back;
	shape.setTexture(&t);
}

void Card::flipFront()
{
	shape.setTexture(&front);
}
