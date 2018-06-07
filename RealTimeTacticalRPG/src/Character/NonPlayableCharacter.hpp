#ifndef DEF_NONPLAYABLECHARACTER
#define DEF_NONPLAYABLECHARACTER

#include "Character.hpp"

class NonPlayableCharacter: Character
{
	private:

	public:
		
		NonPlayableCharacter(std::string name);
		void move(int cellId);

};

#endif

