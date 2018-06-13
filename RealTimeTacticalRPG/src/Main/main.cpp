#include <SFML/Graphics.hpp>
#include "../ResourceHandling/TextureHolder.hpp"

const int width = 1600;
const int height = 900;

int main()
{
	/* Load textures */
	TextureHolder holder;
	holder.load(Textures::Block, "../../assets/cells/rocky.png");
	holder.load(Textures::Free, "../../assets/cells/ground.png");
	
	sf::RenderWindow window(sf::VideoMode(width, height), "Real Time Tactical RPG", sf::Style::Fullscreen);
	window.setFramerateLimit(60);

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
