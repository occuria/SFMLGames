#include "../inc/Card.hpp"
#include <iostream>

Card::Card(boardDimensions bd, Textures::ID pairId)
{
  this->s.setTexture(TextureHolder::get().get(pairId));
  this->s.setColor(sf::Color(50,0,100));
  this->s.setScale(sf::Vector2f(
        bd.cardsize/this->s.getTexture()->getSize().x,
        bd.cardsize/this->s.getTexture()->getSize().y));
	this->pairId = pairId;
	this->isFlipped = false;
}

int Card::flipFront()
{
  /* Check if the card can be flipped on the front side */
	if (this->isFlipped) { return -1; }
	/* Get the card front texture and set it onto the s */
	this->s.setTexture(TextureHolder::get().get((this->pairId)));
	this->s.setColor(sf::Color(255,255,255));
	this->isFlipped = true;
	return 0;
}

int Card::flipBack()
{
  /* Check if the card can be flipped on the front side */
	if (!this->isFlipped) { return -1;	}
	/* Get the card back texture and set it onto the s */
	this->s.setTexture(TextureHolder::get().get((CARDBACK)));
	this->s.setColor(sf::Color(50,0,100));
	this->isFlipped = false;
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
	return this->isFlipped;
}

void Card::pair()
{
	this->isFlipped = true;
}

void Card::unpair()
{
	this->isFlipped = false;
}
