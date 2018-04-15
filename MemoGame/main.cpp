#include <iostream>
#include <SFML/Graphics.hpp>
#include <algorithm>

constexpr int width = 1280;
constexpr int height = 720;
constexpr float spacing = 1.5;

/* returns card size and card spacing in function of board size and number of cards */
std::vector<float> getCardSize(const int nbCards, const int boardSize)
{
	/* Thanks to my friend Varens who gave me these formulas */
	float cardSize = boardSize / (spacing+nbCards);
	float spacingSize = (spacing*boardSize)/(spacing+nbCards)*1/(nbCards+1);
	std::vector<float> res = {cardSize, spacingSize};
	return res;
}

/* Generates the board in function of the number of cards */
std::vector<std::vector<sf::RectangleShape>> generateBoard(int nbX, int nbY, sf::Texture &texture)
{
	std::vector<std::vector<sf::RectangleShape>> board(nbX, std::vector<sf::RectangleShape>(nbY));
	float cardSize = std::min(getCardSize(nbX, width)[0],getCardSize(nbY, height)[0]);
	float spacingSize = std::min(getCardSize(nbX, width)[1],getCardSize(nbY, height)[1]);
	float offsetX = (width-nbX*cardSize-(nbX-1)*spacingSize)/2;
	float offsetY = (height-nbY*cardSize-(nbY-1)*spacingSize)/2;

	for (int i=0; i<nbX; i++) {
		for (int j=0; j<nbY; j++) {
			/* Creates one card and sets its position on the board */
			sf::RectangleShape r(sf::Vector2f(cardSize, cardSize));
			r.setPosition(offsetX+spacingSize*i+cardSize*i, offsetY+spacingSize*j+cardSize*j);
			r.setTexture(&texture);
			r.setOutlineThickness(1);
			r.setOutlineColor(sf::Color::Black);
			board.at(i).push_back(r);
		}
	}
	return board;
}

/* Displays a board of cards */
void displayBoard(sf::RenderWindow &window, std::vector<std::vector<sf::RectangleShape>> board)
{
	for (unsigned int i=0; i<board.size(); i++) {
		for (sf::RectangleShape r : board[i]) {
			window.draw(r);
		}
	}
	return;
}

int main() {
	/*sf::RenderWindow window(sf::VideoMode(width, height), "Memorizing Game", sf::Style::Fullscreen);*/
	sf::RenderWindow window(sf::VideoMode(width, height), "Memorizing Game");
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
	if (!textureC.loadFromFile("./Images/CardBack.jpg")) {
		std::cout << "Error opening card back texture file" << std::endl;
		abort();
	}
	/* Displays the board of cards */
	std::vector<std::vector<sf::RectangleShape>> board;
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
