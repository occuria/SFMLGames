#ifndef DEF_GAME
#define DEF_GAME

#include <vector>

#include "../Cell/Cell.hpp"
#include "../Team/Team.hpp"

class Game
{
	private:

		std::vector<Team> teams;
		std::vector<std::vector<Cell>> board;

	public:

		Game(std::vector<Team>, std::vector<std::vector<Cell>>);
		void display();		
		std::vector<Team> getTeams();
		std::vector<std::vector<Cell>> getBoard();
};

#endif
