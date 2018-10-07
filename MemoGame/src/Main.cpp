#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <algorithm>
#include <random>
#include <map>
#include "../inc/Card.h"
#include "../inc/Game.hpp"
#include "../inc/GameState.h"
#include "../inc/TextureHolder.hpp"

const float width = 1600;
const float height = 900;
const float rspacing = 1;
const int xcards = 5;
const int ycards = 4;

enum Buttons { restart };

/** 
 * Returns {card size, card spacing} in function of board size and card number.
 * Thanks to my friend Varens who helped me find these formulas.
 */
std::vector<float> getCardSize(const int nbX, int nbY, const int width, const int height)
{
	float cardSizeX = width / (rspacing+nbX);
	float spacingSizeX = (rspacing*width)/(rspacing+nbX)*1/(nbX+1);
	float cardSizeY = height / (rspacing+nbY);
	float spacingSizeY = (rspacing*height)/(rspacing+nbY)*1/(nbY+1);
	std::vector<float> res = {std::min(cardSizeX, cardSizeY), std::min(spacingSizeX, spacingSizeY)};
	return res;
}

/* Generates the entity vector, to simplify click management */
std::map<int, sf::RectangleShape> generateEntities(std::vector<std::vector<Card>> board)
{
	std::map<int, sf::RectangleShape> entities;
	for (unsigned int i=0; i<board.size()*board[0].size(); i++) {
		//entities[i] = board[i/board[0].size()][i%board[0].size()].getSprite();
	}
	return entities;
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

void flipCardOnClick(int i, std::vector<std::vector<Card>> &board, std::map<int, Textures::ID> &cardFrontTexture, Textures::ID cardBackId, sf::RenderWindow &window, GameState &state)
{
	switch (state.getState()) {
		case GameState::FirstCard:
			{
				window.clear();
				/* Click on card */
				if (board[i/board[0].size()][i%board[0].size()].flipFront() < 0) {
					return;
				}
				state.flipFirstCard(i/board[0].size(), i%board[0].size(), board[i/board[0].size()][i%board[0].size()].getPairId());
				board[i/board[0].size()][i%board[0].size()].pair();
				break;
			}
		case GameState::SecondCard:
			{
				window.clear();
				/* Click on card */
				if (board[i/board[0].size()][i%board[0].size()].flipFront() < 0) {
					return;
				}
				state.flipSecondCard(i/board[0].size(), i%board[0].size(), board[i/board[0].size()][i%board[0].size()].getPairId());
				break;
			}
		case GameState::pending:
			{
				if (state.endTurn() > 0) {
					std::vector<int> cards = state.getCards();
					board[cards[0]][cards[1]].flipBack();
					board[cards[2]][cards[3]].flipBack();
				}
				break;
			}
	}
	return;
}

/* Click management */
void manageClick(std::map<int, sf::RectangleShape> entities, std::vector<std::vector<Card>> &board, std::map<int, Textures::ID> &cardFrontTexture, Textures::ID cardBackTexture, sf::RenderWindow &window, GameState &state)
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
  /* Creates the window */
	sf::RenderWindow window(sf::VideoMode(width, height), "Memorizing Game", sf::Style::Fullscreen);
	/* Loads resources and initializes the game */
  Game game = Game(rspacing, width, height, xcards, ycards);
  game.loadResources();
  game.initialize();
  game.display(window);
  std::cout << "Main text rect width: " << std::to_string(game.getBoard()[0][0].getSprite().getTextureRect().width) << std::endl;
	/* Initializes the game state */
	GameState state;

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
//				/* Flips a card over when clicked on */
//				case sf::Event::MouseButtonPressed:
//					{
//						if (event.mouseButton.button == sf::Mouse::Left) {
//							manageClick(entities, board, cardFrontTexture, Textures::CardBack, window, state);
//							displayBoard(window, TextureHolder::get()->get(Textures::Background), board, entities);
//							/* Checks if the second card has been flipped over */
//							if (state.endTurn() > 0) {
//								sf::sleep(sf::seconds(1));
//								std::vector<int> cards = state.getCards();
//								board[cards[0]][cards[1]].flipBack();
//								board[cards[2]][cards[3]].flipBack();
//								displayBoard(window, TextureHolder::get()->get(Textures::Background), board, entities);
//							}
//						}
//						break;
//					}
				default:
					break;
			}
		}
	}
	return 0;
}
