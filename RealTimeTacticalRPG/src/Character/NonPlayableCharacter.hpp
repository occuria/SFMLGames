#ifndef DEF_NONPLAYABLECHARACTER
#define DEF_NONPLAYABLECHARACTER

#include "Character.hpp"

class NonPlayableCharacter: public Character
{
	private:

	public:
		
		NonPlayableCharacter(std::string, std::vector<Ability *>);
		void move(int cellId);

};

#endif

