#include "Ability.hpp"

Ability::Ability(std::string name_, int range_, int damage_, int cooldown_, int cast_):
	name(name_), range(range_), damage(damage_), cooldown(cooldown_), cast(cast_) {}

std::string Ability::getName() { return name; }

int Ability::getRange() { return range; }

int Ability::getDamage() { return damage; }

int Ability::getCooldown() { return cooldown; }

int Ability::getCast() { return cast; }
