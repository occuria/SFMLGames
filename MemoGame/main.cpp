#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <algorithm>
#include <random>
#include <map>
#include "Card.h"
#include "GameState.h"
#include "TextureHolder.hpp"

const int width = 1600;
const int height = 900;
const float spacing = 1.5;

enum Buttons { restart };

/* returns card size and card spacing in function of board size and number of cards */
std::vector<float> getCardSize(const int nbX, int nbY, const int width, const int height)
{
	/* Thanks to my friend Varens who gave me these formulas */
	float cardSizeX = width / (spacing+nbX);
	float spacingSizeX = (spacing*width)/(spacing+nbX)*1/(nbX+1);
	float cardSizeY = height / (spacing+nbY);
	float spacingSizeY = (spacing*height)/(spacing+nbY)*1/(nbY+1);
	std::vector<float> res = {std::min(cardSizeX, cardSizeY), std::min(spacingSizeX, spacingSizeY)};
	return res;
}

/* Generates the board in function of the number of cards */
std::vector<std::vector<Card>> generateBoard(const int nbX, const int nbY, const sf::Texture &cardBackTexture)
{
	std::vector<std::vector<Card>> board;
	/* Creates the vector to distribute card front textures */
	std::vector<int> vid;
	for (int i=0; i<nbX*nbY/2; i++) {
		vid.push_back(i);
		vid.push_back(i);
	}
	std::srand(std::time(0));
	std::random_shuffle(std::begin(vid),std::end(vid));
	/* Calculates card size */
	float cardSize = getCardSize(nbX, nbY, width, height)[0];
	float spacingSize = getCardSize(nbX, nbY, width, height)[1];
	float offsetX = (width-nbX*cardSize-(nbX-1)*spacingSize)/2;
	float offsetY = (height-nbY*cardSize-(nbY-1)*spacingSize)/2;

	for (int i=0; i<nbX; i++) {
		std::vector<Card> v;
		for (int j=0; j<nbY; j++) {
			/* Creates a card shape and sets its position on the board */
			sf::RectangleShape s(sf::Vector2f(cardSize, cardSize));
			s.setPosition(offsetX+spacingSize*i+cardSize*i, offsetY+spacingSize*j+cardSize*j);
			s.setTexture(&cardBackTexture);
			s.setTextureRect(sf::IntRect(0, 0, cardBackTexture.getSize().x, cardBackTexture.getSize().y));
			s.setFillColor(sf::Color(50,0,100));
			/* Creates a card and adds it to the card matrix */
			int id = i*nbY+j;
			Card c(s, vid[id]);
			v.push_back(c);
		}
		board.push_back(v);
	}
	return board;
}

/* Generates the entity vector, to simplify click management */
std::map<int, sf::RectangleShape> generateEntities(std::vector<std::vector<Card>> board)
{
	std::map<int, sf::RectangleShape> entities;
	for (unsigned int i=0; i<board.size()*board[0].size(); i++) {
		entities[i] = board[i/board[0].size()][i%board[0].size()].getShape();
	}
	return entities;
}


/* Returns useful board dimensions */
std::vector<float> getBoardDimensions(std::vector<std::vector<Card>> board)
{
	int nbX = board.size();
	int nbY = board[0].size();
	float cardSize = getCardSize(nbX, nbY, width, height)[0];
	float spacingSize = getCardSize(nbX, nbY, width, height)[1];
	float offsetX = (width-nbX*cardSize-(nbX-1)*spacingSize)/2;
	float offsetY = (height-nbY*cardSize-(nbY-1)*spacingSize)/2;
	std::vector<float> dimensions = {cardSize, spacingSize, offsetX, offsetY};
	return dimensions;
}

/* Displays a board of cards */
void displayBoard(sf::RenderWindow &window, sf::Texture frameTexture, std::vector<std::vector<Card>> board, std::map<int, sf::RectangleShape> entities)
{
	int i = board.size()*board[0].size();
	/* Displays the frame */
	sf::RectangleShape frame(sf::Vector2f(width, height));
	frame.setTexture(&frameTexture);
	frame.setTextureRect(sf::IntRect(0,0,width,height));
	window.draw(frame);
	/* Displays restart button */
	sf::Texture restart_b_t;
	if (!restart_b_t.loadFromFile("./Images/restart.png")) {
		std::cout << "Error opening restart button texture file" << std::endl;
		exit(EXIT_FAILURE);
	}
	restart_b_t.setSmooth(true);
	sf::RectangleShape restart_b;
	restart_b.setTexture(&restart_b_t);
	restart_b.setFillColor(sf::Color(50,0,100));
	restart_b.setPosition(50,50);
	restart_b.setSize(sf::Vector2f(getBoardDimensions(board)[0]/2,getBoardDimensions(board)[0]/2));
	if (entities.find(i) == entities.end()) {
		entities[i] = restart_b;
	}
	window.draw(restart_b);
	/* Displays cards */
	for (unsigned int i=0; i<board.size(); i++) {
		for (Card c : board[i]) {
			window.draw(c.getShape());
		}
	}
	window.display();
	return;
}

int allCardsPaired(std::vector<std::vector<Card>> board)
{
	int res = 0;
	for (auto i : board) {
		for (auto j : i) {
			if (!j.isPaired()) {
				res += -1;
			}
		}
	}
	return res;
}

void flipCardOnClick(int i, std::vector<std::vector<Card>> &board, std::map<int, sf::Texture> &cardFrontTexture, sf::Texture &cardBackTexture, sf::RenderWindow &window, GameState &state)
{
	std::cout << "Game state: " << state.getState() << std::endl;
	switch (state.getState()) {
		case GameState::FirstCard:
			{
				std::cout << "Cards paired: " << std::to_string(allCardsPaired(board)) << std::endl;
				window.clear();
				/* Click on card */
				if (board[i/board[0].size()][i%board[0].size()].flipOver(cardFrontTexture[board[i/board[0].size()][i%board[0].size()].getFid()]) < 0) {
					return;
				}
				state.flipFirstCard(i/board[0].size(), i%board[0].size(), board[i/board[0].size()][i%board[0].size()].getFid());
				board[i/board[0].size()][i%board[0].size()].pair();
				break;
			}
		case GameState::SecondCard:
			{
				window.clear();
				/* Click on card */
				if (board[i/board[0].size()][i%board[0].size()].flipOver(cardFrontTexture[board[i/board[0].size()][i%board[0].size()].getFid()]) < 0) {
					return;
				}
				state.flipSecondCard(i/board[0].size(), i%board[0].size(), board[i/board[0].size()][i%board[0].size()].getFid());
				break;
			}
		case GameState::pending:
			{
				if (state.endTurn() > 0) {
					std::vector<int> cards = state.getCards();
					board[cards[0]][cards[1]].flipBack(cardBackTexture);
					board[cards[2]][cards[3]].flipBack(cardBackTexture);
				}
				break;
			}
	}
	return;
}

/* Click management */
void manageClick(std::map<int, sf::RectangleShape> entities, std::vector<std::vector<Card>> &board, std::map<int, sf::Texture> &cardFrontTexture, sf::Texture &cardBackTexture, sf::RenderWindow &window, GameState &state)
{
	unsigned int i=0;
	while (i<entities.size() && !entities[i].getGlobalBounds().contains(sf::Mouse::getPosition().x, sf::Mouse::getPosition().y))
	{
		i++;
	}
	/* Click on card */
	if (i<board.size()*board[0].size()) {
		flipCardOnClick(i, board, cardFrontTexture, cardBackTexture, window, state);
	/* Click on button */
	} else if (i<entities.size() && i>=board.size()*board[0].size()) {
		//exec button function
	}
	/* else : Click on blank */
}

int main() {
	sf::RenderWindow window(sf::VideoMode(width, height), "Memorizing Game", sf::Style::Fullscreen);
	std::cout << "Window created" << std::endl;

	/* Adds the frame texture */
  TextureHolder::get().load(Textures::Background, "./Images/Background.png");
  TextureHolder::get().get(Textures::Background).setRepeated(true);

	/* Adds the card back texture */
  TextureHolder::get().load(Textures::CardBack, "./Images/CardBack.png");
  TextureHolder::get().get(Textures::CardBack).setSmooth(true);

	/* Adds the card front textures vector */
  TextureHolder::get().load(Textures::Giraffe, "./Images/CardFronts/Giraffe.png");
  TextureHolder::get().get(Textures::Giraffe).setSmooth(true);
  TextureHolder::get().load(Textures::Hippo, "./Images/CardFronts/Hippo.png");
  TextureHolder::get().get(Textures::Hippo).setSmooth(true);
  TextureHolder::get().load(Textures::Monkey, "./Images/CardFronts/Monkey.png");
  TextureHolder::get().get(Textures::Monkey).setSmooth(true);
  TextureHolder::get().load(Textures::Penguin, "./Images/CardFronts/Penguin.png");
  TextureHolder::get().get(Textures::Penguin).setSmooth(true);
  TextureHolder::get().load(Textures::Panda, "./Images/CardFronts/Panda.png");
  TextureHolder::get().get(Textures::Panda).setSmooth(true);
  TextureHolder::get().load(Textures::Parrot, "./Images/CardFronts/Parrot.png");
  TextureHolder::get().get(Textures::Parrot).setSmooth(true);
  TextureHolder::get().load(Textures::Pig, "./Images/CardFronts/Pig.png");
  TextureHolder::get().get(Textures::Pig).setSmooth(true);
  TextureHolder::get().load(Textures::Rabbit, "./Images/CardFronts/Rabbit.png");
  TextureHolder::get().get(Textures::Rabbit).setSmooth(true);
  TextureHolder::get().load(Textures::Snake, "./Images/CardFronts/Snake.png");
  TextureHolder::get().get(Textures::Snake).setSmooth(true);
  TextureHolder::get().load(Textures::Elephant, "./Images/CardFronts/Elephant.png");
  TextureHolder::get().get(Textures::Elephant).setSmooth(true);

	/* Generates and displays the board of cards */
	std::vector<std::vector<Card>> board;
	board = generateBoard(5, 4, TextureHolder::get().get(Textures::CardBack));
	std::map<int, sf::RectangleShape> entities;
	entities = generateEntities(board);
	displayBoard(window, TextureHolder::get().get(Textures::Background), board, entities);

	/* Initializes the game state */
	GameState state;
	std::cout << "Game state initialized" << std::endl;
	if (state.getState() == GameState::FirstCard) {
		std::cout << "Game is in FirstCard state after initialization" << std::endl;
		std::cout << "Cards paired: " << std::to_string(allCardsPaired(board)) << std::endl;
	}

	/* Loads the music */
	/*
	sf::Music music;
	if (!music.openFromFile("./Music/music.wav")) {
		std::cout << "Error opening music file" << std::endl;
		abort();
	}
	music.setLoop(true);
	music.play();
	*/

	/* Main loop */
	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			switch(event.type) {
				/* Closes the window */
				case sf::Event::Closed:
					{
						window.close();
						break;
					}
				/* Flips a card over when clicked on */
				case sf::Event::MouseButtonPressed:
					{
						if (event.mouseButton.button == sf::Mouse::Left) {
							manageClick(entities, board, cardFrontTexture, TextureHolder::get().get(Textures::CardBack), window, state);
							displayBoard(window, TextureHolder::get().get(Textures::Background), board, entities);
							/* Checks if the second card has been flipped over */
							if (state.endTurn() > 0) {
								sf::sleep(sf::seconds(1));
								std::vector<int> cards = state.getCards();
								board[cards[0]][cards[1]].flipBack(TextureHolder::get().get(Textures::CardBack));
								board[cards[2]][cards[3]].flipBack(TextureHolder::get().get(Textures::CardBack));
								displayBoard(window, TextureHolder::get().get(Textures::Background), board, entities);
							}
						}
						break;
					}
				default:
					break;
			}
		}
	}
	return 0;
}
