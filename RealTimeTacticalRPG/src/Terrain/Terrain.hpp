#ifndef DEF_TERRAIN
#define DEF_TERRAIN

#include <SFML/Graphics.hpp>

#include "TerrainType.hpp"

class Terrain
{
	private:

		sf::Texture &texture;
		TerrainType type;

	public:
		
		Terrain(sf::Texture &texture_, TerrainType type_);
		sf::Texture &getTexture();
		TerrainType getType();
};

#endif
