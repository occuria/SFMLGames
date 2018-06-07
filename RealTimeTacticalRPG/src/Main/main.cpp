#include <SFML/Graphics.hpp>

const int width = 1600;
const int height = 900;

int main()
{
	sf::RenderWindow window(sf::VideoMode(width, height), "Real Time Tactical RPG", sf::Style::Fullscreen);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();
		window.display();
	}

	return 0;
}
