#include <SFML/Graphics.hpp>

namespace Textures
{
	enum ID { Plain, Rock, Water };
}

class TextureHolder
{
	public:

		static TextureHolder& instance()
		{
			static TextureHolder instance;
			return instance;
		}

		void load(Textures::ID textureID, const std::string &filename);
		sf::Texture& get(Textures::ID textureID);

	private:

		TextureHolder();
		TextureHolder(TextureHolder const&) = delete;
		void operator=(TextureHolder const&) = delete;

		std::map<Textures::ID, sf::Texture> textureMap;
};
