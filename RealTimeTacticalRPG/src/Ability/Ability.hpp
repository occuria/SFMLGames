#ifndef DEF_ABILITY
#define DEF_ABILITY

#include <string>

class Ability
{
	private:

		std::string name;
		int range;
		int damage;
		int cooldown;
		int cast;

	public:

		Ability(std::string, int, int, int, int);
		std::string getName();
		int getRange();
		int getDamage();
		int getCooldown();
		int getCast();
};

#endif
