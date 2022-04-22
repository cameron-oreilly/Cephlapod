#pragma once
#include "Player.h"

#ifndef RANDOMPLAYER_H_
#define RANDOMPLAYER_H_

class RandomPlayer : public Player {
public:
	RandomPlayer(int t) :Player("Random", t) {}
	void getMove(Board board, int&, int&);
};

//Get a random index from STL vectorand expand it into xand y board coordinates
void RandomPlayer::getMove(Board board, int& x, int& y) {
	if (board.isBoardFull())
		return;
	
	int k = board.ecGetVal(rand() % board.ecGetSize());
	
	x = k / board.getCol();
	y = k % board.getCol();

}

#endif /* RANNDOMPLAYER_H_ */

