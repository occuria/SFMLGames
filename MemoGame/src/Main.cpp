#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <algorithm>
#include <random>
#include <map>
#include <thread>
#include <X11/Xlib.h>
#include "../inc/Card.hpp"
#include "../inc/Game.hpp"
#include "../inc/EventHandler.hpp"
#include "../inc/TextureHolder.hpp"

const float width = 1600;
const float height = 900;
const float rspacing = 1;
const int xcards = 5;
const int ycards = 4;

/**
 * Main display loop to be run in a separeted thread.
 */
void loop(sf::RenderWindow& window, Game& game)
{
  while(window.isOpen()) {
    game.display(window);
  }
}

int main() {
  /* Needed to handle multiple graphical threads */
  XInitThreads();
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

	/* Main display loop */
	window.setActive(false);
  std::thread t(&loop, std::ref(window), std::ref(game));

	/* Main event handling loop */
	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
      EventHolder::get().handleEvent(window, game, event);
		}
	}
	return 0;
}
