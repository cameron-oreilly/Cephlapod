#pragma once
#include "Player.h"

#ifndef RANDOMPLAYER_H_
#define RANDOMPLAYER_H_

class RandomPlayer : public Player {
public:
	RandomPlayer(int t) :Player("Random", t) {}
	void getMove(Board board, int&, int&);
};

void RandomPlayer::getMove(Board board, int& x, int& y) {
	if (board.isBoardFull())
		return;
	
	int k = board.emptyCells[rand() % board.emptyCells.size()];
	
	x = k / board.getCol();
	y = k % board.getCol();

	//x = row ;
	//y = col ;
}

#endif /* RANNDOMPLAYER_H_ */

