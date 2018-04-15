#include <iostream>
#include <SFML/Graphics.hpp>
#include <cmath>

constexpr int width = 1280;
constexpr int height = 720;
constexpr float cblank = 1.5;

/* Generates the board according to the number of cards */
std::vector<std::vector<sf::RectangleShape>> generateBoard(int nbcards, sf::Texture &texture)
{
	if (nbcards < 2 || nbcards > 20) {
		std::cout << "Number of cards must be between 2 and 20" << std::endl;
		abort();
	}

	std::vector<std::vector<sf::RectangleShape>> board(nbcards, std::vector<sf::RectangleShape>(nbcards));
	/* Thanks to my friend Varens who gave me these formulas */
	float cardSize = height/(cblank+nbcards);
	float blankSize = (cblank*height)/(cblank+nbcards)*1/(nbcards+1); 

	for (int i=0; i<nbcards; i++) {
		for (int j=0; j<nbcards; j++) {
			/* Creates one card and sets its position on the board */
			sf::RectangleShape r(sf::Vector2f(cardSize, cardSize));
			r.setPosition(blankSize*(i+1)+cardSize*i+(width-height)/2, blankSize*(j+1)+cardSize*j);
			r.setTexture(&texture);
			//r.setTextureRect(sf::IntRect(0,0,300,300));
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
	/* Adds the board texture */
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
	board = generateBoard(6, textureC);
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
