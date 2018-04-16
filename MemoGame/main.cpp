#include <iostream>
#include <SFML/Graphics.hpp>
#include <algorithm>
#include <random>

constexpr int width = 1600;
constexpr int height = 900;
constexpr float spacing = 1.5;

struct Card {
	sf::RectangleShape shape;
	sf::Texture back;
	sf::Texture front;
};

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
std::vector<std::vector<Card>> generateBoard(const int nbX, const int nbY, const sf::Texture &cardBackTexture, const std::vector<sf::Texture> cardFrontTexture)
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
			r.setOutlineThickness(1);
			r.setOutlineColor(sf::Color::Black);
			/* Creates a card and adds it to the card matrix */
			Card c;
			c.shape = r;
			c.back = cardBackTexture;
			c.front = (cardFrontTexture[d(cardFrontTexture.size())-1]);
			c.shape.setTexture(&c.front);
			board[i].push_back(c);
		}
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
			window.draw(c.shape);
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
	std::vector<sf::Texture> cardFrontTexture;
	for (int i=0; i<9; i++) {
		sf::Texture t;
		t.loadFromFile("./Images/MandalaCards/Card" + std::to_string(i+1) +".png");
		std::cout << "./Images/MandalaCards/Card" + std::to_string(i+1) +".png" << std::endl;
		cardFrontTexture.push_back(t);
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
			if (event.type ==sf::Event::KeyPressed) {
				window.clear();
				board[0][0].flipFront();
				displayBoard(window, frameTexture, board);
			}
			*/
		}
	}
	return 0;
}
