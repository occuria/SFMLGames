#include "Game.hpp"

Game::Game(std::vector<Team *> teams_, std::vector<Cell *> board_): teams(teams_), board(board_) {}

void Game::display()
{
	for (auto cell : board) { cell->display(); }
	for (auto team : teams) { team->display(); }
}

std::vector<Team *> Game::getTeams() { return teams; }

std::vector<Cell *> Game::getBoard() { return board; }
