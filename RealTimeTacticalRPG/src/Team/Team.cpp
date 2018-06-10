#include "Team.hpp"
#include "../Character/PlayableCharacter.hpp"
#include "../Character/NonPlayableCharacter.hpp"

Team::Team(std::string name_, std::vector<Character *> characters_): name(name_), characters(characters_) {}

void Team::display() {
	for (auto character : characters) {
		if (PlayableCharacter *ch = dynamic_cast<PlayableCharacter *>(character)) {
			ch->display();
		} else if (NonPlayableCharacter *ch = dynamic_cast<NonPlayableCharacter *>(character)) {
			ch->display();
		}
	}
}

std::string Team::getName() { return name; }

std::vector<Character *> Team::getCharacters() { return characters; }
