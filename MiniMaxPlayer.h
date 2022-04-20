#ifndef MINIMAXPLAYER_H_
#define MINIMAXPLAYER_H_

#include<iostream>
#include<sstream>
#include<limits>

using namespace std;

class MiniMaxPlayer : public Player {
	int playerSymbol;
	double maxMove(Board board);
	double minMove(Board board);
	int steps;

public:
	MiniMaxPlayer(int t) :Player("MiniMax", t) {
		playerSymbol = t;
		steps = 1000; //if the program takes too long, get the limitation of steps back
	}

	void getMove(Board board, int& x, int& y);
};

void MiniMaxPlayer::getMove(Board board, int& x, int& y) {

	priority_queue < Cell > moves;

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			steps = 1000;
			Board tempBoard(board);
			if (!tempBoard.validMove(i, j))
				continue;

			tempBoard.addMove(tempBoard.getTurn(), i, j);
			if (tempBoard.isBoardFull()) {
				if (tempBoard.checkWinningStatus() == playerSymbol) {
					x = i;
					y = j;
					return;
				}
				else {
					continue;
				}
			}
			double minUtility = minMove(tempBoard);
			Cell c(i, j, minUtility);
			moves.push(c);
		}
	}
	if (moves.size() > 0) {
		x = moves.top().x;
		y = moves.top().y;
		cout << moves.size() << " MiniMax Utility = " << moves.top().heuristic
			<< " at (" << (x + 1) << "," << (y + 1) << ")" << endl;
	}

	return;
}

double MiniMaxPlayer::maxMove(Board board) {
	if (board.isBoardFull() || steps <= 0)
		return 0.01;

	double maxUtility = -2;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			Board tempBoard(board);
			if (!tempBoard.validMove(i, j))
				continue;
			tempBoard.addMove(tempBoard.getTurn(), i, j);
			int gameStatus = tempBoard.checkWinningStatus();
			if (gameStatus != -2) {
				if (gameStatus == playerSymbol)
					return 1; //score 1 if wins
				else if (gameStatus == 0)
					return 0; //score 0 if tie
				else
					return -1; //score -1 if lose
			}

			double utility;
			utility = minMove(tempBoard);

			if (utility > maxUtility) {
				maxUtility = utility;
			}
		}
	}
		steps--;
	return maxUtility;
}

double MiniMaxPlayer::minMove(Board board) {
	if (board.isBoardFull() || steps <= 0)
		return 0.01;

	double minUtility = 2;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			Board tempBoard(board);
			if (!tempBoard.validMove(i, j))
				continue;
			tempBoard.addMove(tempBoard.getTurn(), i, j);
			int gameStatus = tempBoard.checkWinningStatus();
			if (gameStatus != -2) {
				if (gameStatus == playerSymbol)
					return 1; //score 1 if wins
				else if (gameStatus == 0)
					return 0; //score 0 if tie
				else
					return -1; //score -1 if lose
			}

			double utility = maxMove(board);

			if (utility < minUtility) {
				minUtility = utility;
			}
		}
	}
		steps--;
	return minUtility;
}

#endif /* MINIMAXPLAYER_H_ */

