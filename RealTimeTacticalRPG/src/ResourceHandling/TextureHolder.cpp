#include "TextureHolder.hpp"

void TextureHolder::load(Textures::ID texturesID, const std::string &filename)
{
	sf::Texture texture;
	texture.loadFromFile(filename);
	textureMap.insert(std::make_pair(texturesID, texture));
}

sf::Texture& TextureHolder::get(Textures::ID textureID)
{
	auto entry = textureMap.find(textureID);
	return entry->second;
}
