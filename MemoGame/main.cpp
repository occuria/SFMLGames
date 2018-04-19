#include <iostream>
#include <SFML/Graphics.hpp>
#include <algorithm>
#include <random>
#include <map>
#include "Card.h"

constexpr int width = 1600;
constexpr int height = 900;
constexpr float spacing = 1.5;

/* allows random draws */
int d(int const nbSides)
{
	static std::random_device rd;
	static std::default_random_engine engine(rd());
	std::uniform_int_distribution<> distribution(1, nbSides);
	return distribution(engine);
}

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
std::vector<std::vector<Card>> generateBoard(const int nbX, const int nbY, const sf::Texture &cardBackTexture, const std::map<int, sf::Texture> cardFrontTexture)
{
	std::vector<std::vector<Card>> board;
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
			s.setOutlineThickness(1);
			s.setOutlineColor(sf::Color::Black);
			/* Creates a card and adds it to the card matrix */
			int id = d(cardFrontTexture.size())-1;
			Card c(s, id);
			c.flipOver(cardBackTexture);
			v.push_back(c);
		}
		board.push_back(v);
	}
	return board;
}

/* Displays a board of cards */
void displayBoard(sf::RenderWindow &window, sf::Texture frameTexture, std::vector<std::vector<Card>> board)
{
	/* Displays the frame */
	sf::RectangleShape frame(sf::Vector2f(width, height));
	frame.setTexture(&frameTexture);
	frame.setTextureRect(sf::IntRect(0,0,width,height));
	window.draw(frame);
	/* Displays cards */
	for (unsigned int i=0; i<board.size(); i++) {
		for (Card c : board[i]) {
			window.draw(c.getShape());
		}
	}
	window.display();
	return;
}

int main() {
	sf::RenderWindow window(sf::VideoMode(width, height), "Memorizing Game", sf::Style::Fullscreen);
	//sf::RenderWindow window(sf::VideoMode(width, height), "Memorizing Game");

	/* Adds the frame texture */
	sf::Texture frameTexture;
	if (!frameTexture.loadFromFile("./Images/Board.jpg")) {
		std::cout << "Error opening frame texture file" << std::endl;
		abort();
	}
	frameTexture.setRepeated(true);

	/* Adds the card back texture */
	sf::Texture cardBackTexture;
	if (!cardBackTexture.loadFromFile("./Images/MandalaCards/CardBack.jpg")) {
		std::cout << "Error opening card back texture file" << std::endl;
		abort();
	}
	cardBackTexture.setSmooth(true);

	/* Adds the card front textures vector */
	std::map<int, sf::Texture> cardFrontTexture;
	for (int i=0; i<9; i++) {
		sf::Texture t;
		t.loadFromFile("./Images/MandalaCards/Card" + std::to_string(i+1) +".png");
		std::cout << "./Images/MandalaCards/Card" + std::to_string(i+1) +".png" << std::endl;
		cardFrontTexture[i] = t;
	}

	/* Displays the board of cards */
	std::vector<std::vector<Card>> board;
	board = generateBoard(6, 3, cardBackTexture, cardFrontTexture);
	displayBoard(window, frameTexture, board);

	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
			/*
			if (event.type == sf::Event::KeyPressed) {
				std::cout << "T'as appuyé sur une touche" << std::endl;
				window.clear();
				board[0][0].getShape().setTexture(&cardBackTexture);
				board[0][0].getShape().setTextureRect(sf::IntRect(0, 0, cardBackTexture.getSize().x, cardBackTexture.getSize().y));
				displayBoard(window, frameTexture, board);
			}
			*/
		}
	}
	return 0;
}
