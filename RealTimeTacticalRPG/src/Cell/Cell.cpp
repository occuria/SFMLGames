#include "Cell.hpp"

int Cell::globalId = 0;

Cell::Cell(Terrain &terrain_): terrain(terrain_)
{
	id = ++globalId;
}

void Cell::display() {}

TerrainType Cell::getType() { return terrain.getType(); }

int Cell::getId() { return id; }
