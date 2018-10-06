#include <SFML/Graphics.hpp>

/**
 * The enumeration of resources, globally available by its namespace.
 */
namespace Textures
{
	enum ID { 
	  /* Global textures */
	  CardBack, Background, 
	  /* Button textures */
	  RestartButton, 
	  /* Front card textures */
	  ElephantFront, GiraffeFront, HippoFront, MonkeyFront, PandaFront, 
	  ParrotFront,PenguinFront, PigFront, RabbitFront, SnakeFront 
	};
}

/**
 * Singleton class that centralizes the management of resources.
 * Uses the ID enum to store and fetch resources.
 */
class TextureHolder
{
	public:

    /**
     * Singleton implementation.
     */
		static TextureHolder& instance()
		{
			static TextureHolder instance;
			return instance;
		}
    
    /**
     * Adds a new resource to the map.
     */
		void load(Textures::ID id, const std::string &filename);

		/**
		 * Gets a resource from the map.
		 */
		sf::Texture& get(Textures::ID id);

	private:

		TextureHolder();
		TextureHolder(TextureHolder const&) = delete;
		void operator=(TextureHolder const&) = delete;

		std::map<Textures::ID, sf::Texture> textureMap;
};
