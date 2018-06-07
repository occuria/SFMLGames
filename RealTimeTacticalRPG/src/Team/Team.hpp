#ifndef DEF_TEAM
#define DEF_TEAM

#include <string>
#include <vector>

#include "../Character/Character.hpp"

class Team
{
	private:

		std::string name;
		std::vector<Character> characters;

	public:

		std::string getName();
		std::vector<Character> getCharacters();
};

#endif
