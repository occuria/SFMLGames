#include <iostream>
#include <SFML/Graphics.hpp>
#include <algorithm>
#include "Card.h"

constexpr int width = 1600;
constexpr int height = 900;
constexpr float spacing = 1.5;

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

/* returns a vector with n card fronts */
std::vector<sf::Image> getCardFronts(int n)
{
	std::vector<sf::Image> res;
	for (int i=0; i<n; i++) {
		sf::Image image;
		image.loadFromFile("./Images/MandalaCards/Card" + std::to_string(i+1) +".png");
		res.push_back(image);
	}
	return res;
}

/* Generates the board in function of the number of cards */
std::vector<std::vector<Card>> generateBoard(int nbX, int nbY, sf::Texture &texture)
{
	std::vector<std::vector<Card>> board(nbX, std::vector<Card>(nbY));
	float cardSize = getCardSize(nbX, nbY, width, height)[0];
	float spacingSize = getCardSize(nbX, nbY, width, height)[1];
	float offsetX = (width-nbX*cardSize-(nbX-1)*spacingSize)/2;
	float offsetY = (height-nbY*cardSize-(nbY-1)*spacingSize)/2;

	for (int i=0; i<nbX; i++) {
		for (int j=0; j<nbY; j++) {
			/* Creates a card shape and sets its position on the board */
			sf::RectangleShape r(sf::Vector2f(cardSize, cardSize));
			r.setPosition(offsetX+spacingSize*i+cardSize*i, offsetY+spacingSize*j+cardSize*j);
			r.setTexture(&texture);
			r.setOutlineThickness(1);
			r.setOutlineColor(sf::Color::Black);
			/* Creates a card and adds it to the card matrix */
			Card c;
			c.setShape(r);
			c.setBack(texture);
			c.setFront(texture);
			board[i].push_back(c);
		}
	}
	return board;
}

/* Displays a board of cards */
void displayBoard(sf::RenderWindow &window, std::vector<std::vector<Card>> board)
{
	for (unsigned int i=0; i<board.size(); i++) {
		for (Card c : board[i]) {
			window.draw(c.getShape());
		}
	}
	return;
}

int main() {
	sf::RenderWindow window(sf::VideoMode(width, height), "Memorizing Game", sf::Style::Fullscreen);
	//sf::RenderWindow window(sf::VideoMode(width, height), "Memorizing Game");

	/* Adds the frame texture */
	sf::Texture textureB;
	if (!textureB.loadFromFile("./Images/Board.jpg")) {
		std::cout << "Error opening board texture file" << std::endl;
		abort();
	}
	/* Displays the frame */
	sf::RectangleShape cadre(sf::Vector2f(width, height));
	cadre.setTexture(&textureB);
	cadre.setTextureRect(sf::IntRect(0,0,width,height));
	window.draw(cadre);

	/* Adds the card back texture */
	sf::Texture textureC;
	if (!textureC.loadFromFile("./Images/MandalaCards/CardBack.jpg")) {
		std::cout << "Error opening card back texture file" << std::endl;
		abort();
	}
	textureC.setSmooth(true);
	/* Displays the board of cards */
	std::vector<std::vector<Card>> board;
	board = generateBoard(6, 3, textureC);
	displayBoard(window, board);

	window.display();
	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
		}
	}
	return 0;
}
