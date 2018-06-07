#ifndef DEF_PLAYABLECHARACTER
#define DEF_PLAYABLECHARACTER

#include "Character.hpp"

class PlayableCharacter: Character
{
	private:

	public:
		
		PlayableCharacter(std::string name);
		void move(int cellId);

};

#endif

