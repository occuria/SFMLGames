#include "PlayableCharacter.hpp"

PlayableCharacter::PlayableCharacter(std::string name_, std::vector<Ability *> abilities_):
	Character(name_, abilities_) {}

void Character::move(int cellId) {
	cellId = 0;
}
