#include "TextureHolder.hpp"

void TextureHolder::load(Textures::ID texturesID, const std::string &filename)
{
	std::unique_ptr<sf::Texture> texture(new sf::Texture());
	texture->loadFromFile(filename);
	textureMap.insert(std::make_pair(texturesID, std::move(texture)));
}

sf::Texture& TextureHolder::get(Textures::ID textureID)
{
	auto entry = textureMap.find(textureID);
	return *entry->second;
}
