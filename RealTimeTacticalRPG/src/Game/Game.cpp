#include "Game.hpp"

Game::Game(std::vector<Team *> teams_, std::vector<std::vector<Cell *>> board_): teams(teams_), board(board_) {}

void Game::display()
{
	for (auto row : board) { for (auto cell : row) { cell->display(); } }
	for (auto team : teams) { team->display(); }
}

std::vector<Team *> Game::getTeams() { return teams; }

std::vector<std::vector<Cell *>> Game::getBoard() { return board; }
