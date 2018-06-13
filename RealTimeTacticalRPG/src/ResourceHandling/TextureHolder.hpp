#include <SFML/Graphics.hpp>

namespace Textures
{
	enum ID { Free, Block };
}

class TextureHolder
{
	public:

		void load(Textures::ID textureID, const std::string &filename);
		sf::Texture &get(Textures::ID textureID);

	private:

		std::map<Textures::ID, std::unique_ptr<sf::Texture>> TextureMap;
};

