#ifndef DEF_TEXTURE_HOLDER
#define DEF_TEXTURE_HOLDER

#include <SFML/Graphics.hpp>
#include <boost/preprocessor.hpp>

/**
 * Uses boost/preprocessor to automatically generate an EnumToString function 
 * for enums declared with the DEFINE_ENUM_WITH_STRING_CONVERSIONS macro.
 */
#define X_DEFINE_ENUM_WITH_STRING_CONVERSIONS_TOSTRING_CASE(r, data, elem)      \
  case elem : return BOOST_PP_STRINGIZE(elem);

#define DEFINE_ENUM_WITH_STRING_CONVERSIONS(name, enumerators)                  \
  enum name {                                                                   \
    BOOST_PP_SEQ_ENUM(enumerators)                                              \
  };                                                                            \
                                                                                \
  inline const char* EnumToString(name v)                                       \
  {                                                                             \
    switch (v)  {                                                               \
      BOOST_PP_SEQ_FOR_EACH(                                                    \
        X_DEFINE_ENUM_WITH_STRING_CONVERSIONS_TOSTRING_CASE,                    \
        name,                                                                   \
        enumerators                                                             \
      )                                                                         \
      default: return "[Unknown " BOOST_PP_STRINGIZE(name) "]";                 \
    }                                                                           \
  }

/**
 * The enumeration of resources, globally available by its namespace.
 */
namespace Textures
{
  DEFINE_ENUM_WITH_STRING_CONVERSIONS(ID,
	  /* Global textures */
	  (GlobalOffset)(CardBack)(Background)
	  /* Button textures */
	  (ButtonOffset)(RestartButton)
	  /* Front card textures */
	  (FrontOffset)(Elephant)(Giraffe)(Hippo)(Monkey)(Panda)(Parrot)(Penguin)(Pig)
	  (Rabbit)(Snake)
	  /* Last item */
	  (Last)
  )
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
		static TextureHolder& get()
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

		TextureHolder(TextureHolder const&) = delete;
		void operator=(TextureHolder const&) = delete;
		TextureHolder() = default;

		std::map<Textures::ID, sf::Texture> textureMap;

};

#endif
