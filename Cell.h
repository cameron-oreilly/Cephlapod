/*
 * Cell.h
 *
 *  Created on: 27 Feb 2022
 *      Author: dongmo
 */

#ifndef CELL_H_
#define CELL_H_

struct Cell {
	int x;
	int y;
	int heuristic;

	Cell(int xx, int yy, int hh):x(xx), y(yy), heuristic(hh) {}

	bool operator<(const Cell& c) const {
		return abs(heuristic) < abs(c.heuristic);
	}
	bool operator==(const Cell& c) const {
		return (x == c.x && y == c.y);
	}
};



#endif /* CELL_H_ */
