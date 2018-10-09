#include <iostream>
#include "../inc/Game.hpp"

Game::Game(float rspacing, float width, float height, int xcards, int ycards):
 bd(boardDimensions(rspacing, width, height, xcards, ycards))
{}

void Game::loadResources()
{
	/* Loads the background texture */
  TextureHolder::get().load(Textures::Background, "resources/Background.png");
  TextureHolder::get().get(Textures::Background).setRepeated(true);

	/* Loads the card back texture */
  TextureHolder::get().load(Textures::CardBack, "resources/CardBack.png");
  TextureHolder::get().get(Textures::CardBack).setSmooth(true);

	/* Loads the card front textures vector */
  for (int i=Textures::FrontOffset+1; i<Textures::Last; i++) {
    TextureHolder::get().load((Textures::ID)i, std::string(
          "resources/CardFronts/") + EnumToString((Textures::ID)i) + ".png");
    TextureHolder::get().get((Textures::ID)i).setSmooth(true);
    texMap[i-(Textures::FrontOffset+1)] = (Textures::ID)i;
  }
}

void Game::initialize()
{
	/* Creates the textures id vector to randomly distribute card front textures */
	std::vector<Textures::ID> pairIdV;
	int enumOffset = Textures::FrontOffset+1;
	for (int i=enumOffset; i<enumOffset+this->bd.xcards*this->bd.ycards/2; i++) {
		pairIdV.push_back((Textures::ID)i);
		pairIdV.push_back((Textures::ID)i);
	}
	std::srand(std::time(0));
	std::random_shuffle(std::begin(pairIdV),std::end(pairIdV));

  /* Fills the board, i.e. the 2 dimensions vector of cards */
	for (int i=0; i<this->bd.xcards; i++) {
    std::vector<Card> v;
		for (int j=0; j<this->bd.ycards; j++) {
			/* Creates a card */
			Card c = Card(this->bd, pairIdV[i*this->bd.ycards+j]);
      /* Sets its position on the board */
			c.getSprite().setPosition(
			    this->bd.xoffset+this->bd.spacing*i+this->bd.cardsize*i,
			    this->bd.yoffset+this->bd.spacing*j+this->bd.cardsize*j);
			/* Adds the card to the board */
			v.push_back(c);
		}
		this->board.push_back(v);
	}
}

void Game::display(sf::RenderWindow& window)
{
  /* Displays the background */
	sf::RectangleShape frame(sf::Vector2f(window.getSize().x, window.getSize().y));
	frame.setTextureRect(sf::IntRect(0,0,window.getSize().x, window.getSize().y));
	frame.setTexture(&TextureHolder::get().get(Textures::Background));
	window.draw(frame);
	/* Displays cards */
	for (std::vector<Card> vc : board) {
	  for (Card c : vc) {
	    window.draw(c.getSprite());
    }
  }
  /* Displays the previously constructed view */
  window.display();
}

int Game::manageEvent(sf::Vector2f pos)
{
  sf::Vector2i v;
  v = this->em.manageClick(this->board, pos);
  if (v.x == -1 && v.y == -1) {
    return 0;
  }
  return flipCard(v);
}

int Game::flipCard(sf::Vector2i pos)
{
  /* Checks wether a card has been clicked on or not */

  Card& c = this->board[pos.x][pos.y];
  /* Stops here if the card is already flipped on the front side */
  if (c.isPaired()) { return -1; }
  /* Flips the card if the game is in the right state */
  cardId cid = { (Textures::ID)c.getPairId(), pos };
  switch (this->gs.flipCardState(cid)) { 
    case 1 : {
      /* Flip cards back */
      std::vector<sf::Vector2i> v = this->gs.getCards();
      board[v[0].x][v[0].y].flipBack();
      board[v[1].x][v[1].y].flipBack();
      break; }
    default :
      /* Do not flip cards back */
      break;
  }
  return 0;
}

bool Game::areAllCardsPaired()
{
  bool res = true;
  for (std::vector<Card> vc : this->board) {
    for (Card c : vc) {
      res = res && c.isPaired();
    }
  }
  return res;
}

std::map<int, Textures::ID> Game::getTexMap()
{
  return this->texMap;
}

std::vector<std::vector<Card>> Game::getBoard()
{
  return this->board;
}
