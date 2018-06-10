#include "Cell.hpp"
#include "CellType.hpp"

int Cell::globalId = 0;

Cell::Cell()
{
	id = ++globalId;
	occupied = false;
	type = CellType::Free;
}

void Cell::display() {}

int Cell::getId() { return id; }

bool Cell::isOccupied() { return occupied; }
