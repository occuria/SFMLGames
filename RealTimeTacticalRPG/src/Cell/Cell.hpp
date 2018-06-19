#ifndef DEF_CELL
#define DEF_CELL

#include "../Terrain/Terrain.hpp"

class Cell
{
	private:

		int id;
		static int globalId;
		Terrain &terrain;

	public:
		
		Cell(Terrain &terrain_);
		void display();
		TerrainType getType();
		int getId();
};

#endif
