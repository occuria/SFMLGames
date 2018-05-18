#include "Card.h"
#include <iostream>

Card::Card()
{
	paired = false;
}

Card::Card(sf::RectangleShape s, int id)
{
	shape = s;
	fid = id;
	paired = false;
}

int Card::flipOver(const sf::Texture &t)
{
	if (paired) {
		return -1;
	}
	shape.setTexture(&t);
	shape.setTextureRect(sf::IntRect(0, 0, t.getSize().x, t.getSize().y));
	shape.setFillColor(sf::Color(255,255,255));
	paired = true;
	return 0;
}

int Card::flipBack(const sf::Texture &t)
{
	if (!paired) {
		return -1;
	}
	shape.setTexture(&t);
	shape.setTextureRect(sf::IntRect(0, 0, t.getSize().x, t.getSize().y));
	shape.setFillColor(sf::Color(50,0,100));
	paired = false;
	return 0;
}

sf::RectangleShape &Card::getShape()
{
	return shape;
}

int Card::getFid()
{
	return fid;
}

bool Card::isPaired()
{
	return paired;
}

void Card::pair()
{
	paired = true;
}

void Card::unpair()
{
	paired = false;
}
