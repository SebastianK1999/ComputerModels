#include "Board.h"

#include <random>
#include <vector>
#include "Cell.h"

std::random_device Board::rd;
std::mt19937_64 Board::gen(Board::rd());
std::uniform_real_distribution<> Board::distr(0,1);

Board::Board(size_t _n) :
	n(_n),
	pixelSize(10)
{
	cells.reserve(n);
	for (size_t i = 0; i < n; i++) {
		cells.emplace_back(std::vector<Cell>());
		cells.back().reserve(n);
		for (size_t j = 0; j < n; j++) {
			cells.back().emplace_back(Cell(i*pixelSize,j*pixelSize, Board::distr(Board::rd) > 0.5));
		}
	}
}

inline size_t Board::checkNeighbour(size_t _x, size_t _y) {
	return (cells[_x % n][_y % n].isAlive ? 1 : 0);
}

void Board::run() {
	for (size_t i = 0; i < n; i++) {
		for (size_t j = 0; j < n; j++) {
			cells[i][j].neighbourCount =
				checkNeighbour(i - 1, j - 1) +
				checkNeighbour(i, j - 1) +
				checkNeighbour(i + 1, j - 1) +
				checkNeighbour(i - 1, j) +
				checkNeighbour(i + 1, j) +
				checkNeighbour(i - 1, j + 1) +
				checkNeighbour(i, j + 1) +
				checkNeighbour(i + 1, j + 1);
		}
	}
	for (size_t i = 0; i < n; i++) {
		for (size_t j = 0; j < n; j++) {
			Cell& cur = cells[i][j];
			if (cur.isAlive) {
				if (cur.neighbourCount == 3 || cur.neighbourCount == 2) cur.isAlive = true;
				else cur.isAlive = false;
			}
			else if (cur.neighbourCount == 3) cur.isAlive = true;
			else cur.isAlive = false;
		}
	}
}

void Board::draw() {
	for (size_t i = 0; i < n; i++) {
		for (size_t j = 0; j < n; j++) {
			if (cells[i][j].isAlive) {
				ofSetColor(255,0,0);
				ofDrawRectangle(
					cells[i][j].getX(),
					cells[i][j].getY(),
					pixelSize,
					pixelSize
				);
			}
		}
	}
}