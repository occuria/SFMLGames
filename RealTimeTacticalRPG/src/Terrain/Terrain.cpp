#include "Terrain.hpp"

Terrain::Terrain(sf::Texture &texture_, TerrainType type_): texture(texture_), type(type_) {};

sf::Texture &Terrain::getTexture() { return texture; }

TerrainType Terrain::getType() { return type; }
