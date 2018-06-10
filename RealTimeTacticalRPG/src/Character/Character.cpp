#include "Character.hpp"

Character::Character(std::string name_, std::vector<Ability *> abilities_):
	name(name_), abilities(abilities_),	maxHealth(100), curHealth(maxHealth) {}

void Character::display() {}

std::string Character::getName() { return name; }

int Character::getMaxHealth() { return maxHealth; }

int Character::getCurHealth() { return curHealth; }
