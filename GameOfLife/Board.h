#pragma once
#include <random>
#include <vector>
#include "Cell.h"

class Board{
private:
	static std::random_device rd;
	static std::mt19937_64 gen;
	static std::uniform_real_distribution<double> distr;

	std::vector<std::vector<Cell>> cells;
	inline size_t checkNeighbour(size_t _x, size_t _y);
	size_t pixelSize;
	const size_t n;

public:
	Board(size_t n);
	void run();
	void draw();


};

