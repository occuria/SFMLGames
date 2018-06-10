#ifndef DEF_PLAYABLECHARACTER
#define DEF_PLAYABLECHARACTER

#include "Character.hpp"

class PlayableCharacter: public Character
{
	private:

	public:
		
		PlayableCharacter(std::string, std::vector<Ability *>);
		void move(int cellId);

};

#endif

