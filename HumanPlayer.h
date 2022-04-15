/*
 *
 *  Created on: 25/02/2022
 *      Author: dongmo
 */

#ifndef HUMANPLAYER_H_
#define HUMANPLAYER_H_

class HumanPlayer: public Player {
public:
	HumanPlayer(int t):Player("Human", t){}
	void getMove(Board board, int&, int&);
};

void HumanPlayer::getMove(Board board, int& x, int& y)
{
	if(board.isBoardFull())
		return;

	do {
		cout << "Input your move with row and column numbers:" << endl;
		int row, col;
		cin >> row >> col; 
		x = row-1;
		y = col-1;
	} while (!board.validMove(x,y));
}

#endif /* HUMANPLAYER_H_ */
