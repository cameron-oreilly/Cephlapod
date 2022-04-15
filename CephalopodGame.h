/*
 *
 *  Created on: 25/02/2022
 *      Author: dongmo
 */

#ifndef CEPHALOPODGAME_H_
#define CEPHALOPODGAME_H_


class CephalopodGame
{
private:
	Board board;
	Player* players[2];
public:
	CephalopodGame(const Board& b, Player* p[]): board(b) {
		players[0] = p[0];
		players[1] = p[1];
	}

	int play();
};

int CephalopodGame::play() {

	board.printBoard();

	do {
		int x=0, y=0;
		int playerIndex = (board.getTurn() == 1)? 0:1;

		players[playerIndex]->getMove(board,x,y);
		cout << players[playerIndex]->getPlayerName() << "'s move: (" << (x+1) << ", " << (y+1) << ")" << endl;

		board.addMove(board.getTurn(), x, y);
		board.printBoard();
	} while (!board.isBoardFull());

	int winner = board.checkWinningStatus();
	int playerIndex = (winner == 1)? 0:1;
	if (winner != 0) {
		cout << "The winner is " << players[playerIndex]->getPlayerName()  << ". Congratulations!" << endl;
		return winner;
	} else {
		cout <<"Draw game!" << endl;
		return 0;
	}
}

#endif /* CEPHALOPODGAME_H_ */
