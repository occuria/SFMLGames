#ifndef DEF_GAME
#define DEF_GAME

#include <vector>

#include "../Cell/Cell.hpp"
#include "../Team/Team.hpp"

class Game
{
	private:

		std::vector<Team> teams;
		std::vector<Cell> board;

	public:

		std::vector<Team> getTeams();
		std::vector<Cell> getBoard();
};

#endif
