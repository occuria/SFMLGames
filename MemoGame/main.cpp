#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <algorithm>
#include <random>
#include <map>
#include "Card.h"
#include "GameState.h"

const int width = 1600;
const int height = 900;
const float spacing = 1.5;

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
void displayBoard(sf::RenderWindow &window, sf::Texture frameTexture, std::vector<std::vector<Card>> board)
{
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
	sf::Sprite restart_b;
	restart_b.setTexture(restart_b_t);
	restart_b.setColor(sf::Color(50,0,100));
	restart_b.setPosition(50,50);
	restart_b.setScale(0.5,0.5);
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

/* Click management */
void flipCardOnClick(std::vector<std::vector<Card>> &board, std::map<int, sf::Texture> &cardFrontTexture, sf::Texture &cardBackTexture, sf::RenderWindow &window, GameState &state)
{
	unsigned int i=0;
	while (i<board.size()*board[0].size() && !board[i/board[0].size()][i%board[0].size()].getShape().getGlobalBounds().contains(sf::Mouse::getPosition().x, sf::Mouse::getPosition().y)) {
		i++;
	}
	std::cout << "Game state: " << state.getState() << std::endl;
	switch (state.getState()) {
		case GameState::FirstCard:
			{
				std::cout << "Cards paired: " << std::to_string(allCardsPaired(board)) << std::endl;
				window.clear();
				/* Click on blank */
				if (i == board.size()*board[0].size()) {
					return;
				}
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
				/* Click on blank */
				if (i == board.size()*board[0].size()) {
					return;
				}
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

int main() {
	sf::RenderWindow window(sf::VideoMode(width, height), "Memorizing Game", sf::Style::Fullscreen);

	/* Adds the frame texture */
	sf::Texture frameTexture;
	if (!frameTexture.loadFromFile("./Images/Background.png")) {
		std::cout << "Error opening frame texture file" << std::endl;
		exit(EXIT_FAILURE);
	}
	frameTexture.setRepeated(true);

	/* Adds the card back texture */
	sf::Texture cardBackTexture;
	if (!cardBackTexture.loadFromFile("./Images/CardBack.png")) {
		std::cout << "Error opening card back texture file" << std::endl;
		exit(EXIT_FAILURE);
	}
	cardBackTexture.setSmooth(true);

	/* Adds the card front textures vector */
	std::map<int, sf::Texture> cardFrontTexture;
	std::vector <std::string> cardFronts {"giraffe", "hippo", "monkey", "penguin", "panda", "parrot", "pig", "rabbit", "snake", "elephant"};
	int j=0;
	for (auto i : cardFronts) {
		sf::Texture t;
		if (!t.loadFromFile("./Images/CardFronts/" + i + ".png")) {
			exit(EXIT_FAILURE);
		}
		t.setSmooth(true);
		cardFrontTexture[j] = t;
		j++;
	}

	/* Displays the board of cards */
	std::vector<std::vector<Card>> board;
	board = generateBoard(5, 4, cardBackTexture);
	displayBoard(window, frameTexture, board);

	/* Initializes the game state */
	GameState state;
	std::cout << "Game state initialized" << std::endl;
	if (state.getState() == GameState::FirstCard) {
		std::cout << "Game is in FirstCard state after initialization" << std::endl;
		std::cout << "Cards paired: " << std::to_string(allCardsPaired(board)) << std::endl;
	}

	/* Loads the music */
	sf::Music music;
	if (!music.openFromFile("./Music/music.wav")) {
		std::cout << "Error opening music file" << std::endl;
		abort();
	}
	music.setLoop(true);
	music.play();

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
							flipCardOnClick(board, cardFrontTexture, cardBackTexture, window, state);
							displayBoard(window, frameTexture, board);
							/* Checks if teh second card has been flipped over */
							if (state.endTurn() > 0) {
								sf::sleep(sf::seconds(1));
								std::vector<int> cards = state.getCards();
								board[cards[0]][cards[1]].flipBack(cardBackTexture);
								board[cards[2]][cards[3]].flipBack(cardBackTexture);
								displayBoard(window, frameTexture, board);
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
