#pragma once
#include "ofMain.h"

class Cell
{
private:
	static Cell nullCelll;
	
	size_t screen_x;
	size_t screen_y;

public:
	size_t getX();
	size_t getY();
	bool isAlive;
	size_t neighbourCount;

	Cell();
	Cell(size_t _x, size_t _y, bool _alive);

};

