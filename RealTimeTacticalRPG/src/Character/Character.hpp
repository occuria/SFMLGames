#ifndef DEF_CHARACTER
#define DEF_CHARACTER

#include <string>
#include <vector>

#include "../Ability/Ability.hpp"

class Character
{
	private:

		std::string name;
		std::vector<Ability> abilities;
		int maxHealth;
		int curHealth;

	public:
		
		Character(std::string name);
		std::string getName();
		int getMaxHealth();
		int getCurHealth();
		virtual void move(int cellId) = 0;
};

#endif
