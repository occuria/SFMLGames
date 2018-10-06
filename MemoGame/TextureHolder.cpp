#include "TextureHolder.hpp"

void TextureHolder::load(Textures::ID id, const std::string &filename)
{
	sf::Texture texture;
	texture.loadFromFile(filename);
	textureMap.insert(std::make_pair(id, texture));
}

sf::Texture& TextureHolder::get(Textures::ID id)
{
	auto entry = textureMap.find(id);
	return entry->second;
}
