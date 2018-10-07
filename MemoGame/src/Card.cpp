#include "../inc/Card.h"
#include <iostream>

Card::Card(boardDimensions bd, Textures::ID pairId)
{
  this->s.setTexture(TextureHolder::get()->get(CARDBACK));
  this->s.setColor(sf::Color(50,0,100));
  this->s.setScale(sf::Vector2f(
        bd.cardsize/this->s.getTexture()->getSize().x,
        bd.cardsize/this->s.getTexture()->getSize().y));
	this->pairId = pairId;
	this->paired = false;
}

int Card::flipFront()
{
  /* Check if the card can be flipped on the front side */
	if (isPaired()) { return -1; }
	/* Get the card front texture and set it onto the s */
  sf::Texture t = TextureHolder::get()->get((this->pairId));
	this->s.setTexture(t);
	this->s.setColor(sf::Color(255,255,255));
	paired = true;
	return 0;
}

int Card::flipBack()
{
  /* Check if the card can be flipped on the front side */
	if (!isPaired()) { return -1;	}
	/* Get the card back texture and set it onto the s */
  sf::Texture t = TextureHolder::get()->get((CARDBACK));
	this->s.setTexture(t);
	this->s.setColor(sf::Color(50,0,100));
	paired = false;
	return 0;
}

sf::Sprite& Card::getSprite()
{
	return this->s;
}

int Card::getPairId()
{
	return this->pairId;
}

bool Card::isPaired()
{
	return this->paired;
}

void Card::pair()
{
	this->paired = true;
}

void Card::unpair()
{
	this->paired = false;
}
