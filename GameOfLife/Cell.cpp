#include "Cell.h"

Cell Cell::nullCelll = Cell();

Cell::Cell():
	Cell(0,0,false)
{

}

Cell::Cell(size_t _x, size_t _y, bool _alive):
	screen_x(_x),
	screen_y(_y),
	isAlive(_alive),
	neighbourCount(0)
{

}

size_t Cell::getX() {
	return screen_x;
}

size_t Cell::getY() {
	return screen_y;
}