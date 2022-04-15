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
		return heuristic < c.heuristic;
	}
};



#endif /* CELL_H_ */
