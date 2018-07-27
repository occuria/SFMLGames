#include "Menu.hpp"
#include "../ResourceHandling/TextureHolder.hpp"
#include "../Game/Game.hpp"

Menu::Menu()
{
	TextureHolder::instance().load(Textures::Plain, "../../assets/cells/ground.png");
	TextureHolder::instance().load(Textures::Rock, "../../assets/cells/rocky.png");
	TextureHolder::instance().load(Textures::Water, "../../assets/cells/water.png");
}

void Menu::launchGame()
{
	Game game;
}
