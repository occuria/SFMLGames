#include "Card.h"
#include <iostream>

Card::Card(sf::RectangleShape s, int id)
{
	shape = s;
	fid = id;
	upturned = false;
}

void Card::flipOver(const sf::Texture &t)
{
	shape.setTexture(&t);
	shape.setTextureRect(sf::IntRect(0, 0, t.getSize().x, t.getSize().y));
}

sf::RectangleShape &Card::getShape()
{
	return shape;
}

int Card::getFid()
{
	return fid;
}

bool Card::getUpturned()
{
	return upturned;
}

/*
void Card::setShape(sf::RectangleShape r)
{
	shape = r;
}
*/

void Card::setUpturned(bool u)
{
	upturned = u;
}
