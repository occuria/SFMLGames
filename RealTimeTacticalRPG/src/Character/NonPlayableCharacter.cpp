#include "NonPlayableCharacter.hpp"

NonPlayableCharacter::NonPlayableCharacter(std::string name_, std::vector<Ability *> abilities_):
	Character(name_, abilities_) {}

void Character::move(int cellId) {
	cellId = 0;
}
