
#ifndef COMPUTERPLAYER_H_
#define COMPUTERPLAYER_H_

class ComputerPlayer : public Player {
	int playerSymbol;
public:
	ComputerPlayer(int t) :Player("ComputerPlayer", t) {
		playerSymbol = t;
	}

	void getMove(Board board, int& x, int& y) {
		if (board.isBoardFull())
			return;

		priority_queue<Cell> moves;

		for (int i = 0; i < board.getRow(); i++) {
			for (int j = 0; j < board.getCol(); j++) {
				Board tempBoard(board);
				if (tempBoard.validMove(i, j)) {
					tempBoard.addMove(playerSymbol, i, j);
					Cell c(i, j, tempBoard.heuristic(playerSymbol));
					moves.push(c);
				}
			}
		}

		if (moves.size() > 0) {
			x = moves.top().x;
			y = moves.top().y;
		}
		else {
			cout << "Can't find a new replacement" << endl;
		}

		cout << "Heuristic = " << moves.top().heuristic << " at ("
			<< (x + 1) << "," << (y + 1) << ")" << endl;
	}
};

#endif /* COMPUTERPLAYER_H_ */