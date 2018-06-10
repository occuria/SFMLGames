#ifndef DEF_CELL
#define DEF_CELL

#include "CellType.hpp"

class Cell
{
	private:

		int id;
		static int globalId;
		bool occupied;
		CellType type;

	public:
		
		Cell();
		void display();
		int getId();
		bool isOccupied();
};

#endif
