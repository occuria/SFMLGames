#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <algorithm>
#include <random>
#include <map>
#include "../inc/Card.h"
#include "../inc/Game.hpp"
#include "../inc/GameState.h"
#include "../inc/EventManager.hpp"
#include "../inc/TextureHolder.hpp"

const float width = 1600;
const float height = 900;
const float rspacing = 1;
const int xcards = 5;
const int ycards = 4;

int main() {
  /* Creates the window */
	sf::RenderWindow window(sf::VideoMode(width, height), 
	    "Memorizing Game", sf::Style::Fullscreen);
	/* Loads resources and initializes the game, with its game state and event
	 * manager */
  Game game = Game(rspacing, width, height, xcards, ycards);
  game.loadResources();
  game.initialize();

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
		  /* Catch event */
			switch(event.type) {
				/* Window closure */
				case sf::Event::Closed:
					{
						window.close();
						break;
					}
				/* Click */
      case sf::Event::MouseButtonPressed:
					{
						if (event.mouseButton.button == sf::Mouse::Left) {
              std::cout << "oolilol" << std::endl;
						  game.manageEvent(sf::Vector2f(
						        event.mouseButton.x,event.mouseButton.y));
              game.display(window);
            }
						break;
					}
				default:
					break;
			}
		}
    game.display(window);
	}
	return 0;
}
