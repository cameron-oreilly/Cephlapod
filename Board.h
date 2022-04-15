/*
 * Board.h
 *
 *  Created on: 25/02/2022
 *      Author: dongmo
 */

#ifndef BOARD_H_
#define BOARD_H_

class Board {
private:
	int row, col;
	int player; //1 = white; -1 = black
	int **grid; // 0 = empty; other values for pip count; positive for white; negative for black

public:

	vector<int> emptyCells;

	Board(int r, int c) :
			row(r), col(c) {
		grid = new int*[row];
		for (int i = 0; i < row; i++)
			grid[i] = new int[col];

		for (int i = 0; i < row; i++) {
			for (int j = 0; j < col; j++) {
				grid[i][j] = 0;
				emptyCells.push_back(i * col + j); // init indicies of empty cells (k = x * n + y)
			}
		}

		player = 1; // white has the first turn
	}

	~Board() {
		for (int i = 0; i < row; i++)
			delete[] grid[i];

		delete[] grid;
	}

	Board(const Board &cboard) {//Copy constructor
		row = cboard.row;
		col = cboard.col;

		grid = new int*[row];
		for (int i = 0; i < row; i++)
			grid[i] = new int[col];

		for (int i = 0; i < row; i++)
			for (int j = 0; j < col; j++) {
				grid[i][j] = cboard.grid[i][j];
			}
		for (int i = 0; i < cboard.emptyCells.size(); i++) {
			emptyCells.push_back(cboard.emptyCells[i]);
		}

		player = cboard.getTurn();
	}

	bool isBoardFull() {
		for (int i = 0; i < row; i++) {
			for (int j = 0; j < col; j++) {
				if(grid[i][j] == 0)
					return false;
			}
		}
		return true;
	}

	int getTurn() const {
		return player;
	}

	bool validMove(int x, int y);

	bool addMove(int player, int x, int y);

	int checkWinningStatus();

	void printBoard();

	int capturingPlacement(int x, int y);//to be implemented

	int getCol();

	int getRow();

};

// CURRENTLY ONLY DOES PIP COUNT TODO:: EXTEND CODE TO CAPTURE!!!
int Board::capturingPlacement(int x, int y) {
	const int OFFSETX[] = { 0, 1, 0, -1 };
	const int OFFSETY[] = { -1, 0, 1, 0 };

	int sum = 0;

	queue<int> neighbourValues;

	// populate queue with neighbours absolute values
	for (int i = 0; i < 4; i++) {
		int nx = x + OFFSETX[i];
		int ny = y + OFFSETY[i];
		if (!(nx < 0 || ny < 0 || nx >= row || ny >= col)) {
			neighbourValues.push(abs(grid[nx][ny]));
		}
	}

	// process queue into sum
	while (!neighbourValues.empty()) {
		sum += neighbourValues.front();
		neighbourValues.pop();
	}

	return sum;
	return 1;
}

int Board::checkWinningStatus() {
	if (!isBoardFull())
		return -2; //error message

	int counter = 0;

	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			if (grid[i][j] > 0)
				counter++;
		}
	}

	if (counter * 2 > row * col)
		return 1; //white player won
	else if (counter * 2 < row * col)
		return -1; //black player won
	else
		return 0;//draw
}

bool Board::validMove(int x, int y) {

	if (x < 0 || y < 0 || x > row - 1 || y > col - 1) {
		return false;
	}

	if (grid[x][y] != 0) {
		return false;
	}

	return true;
}

bool Board::addMove(int p, int x, int y) {
	if (p != player) {
		cout << "It is not the player's turn!" << endl;
		return false;
	}

	if (!validMove(x, y))
		return false;

	if (capturingPlacement(x, y) != 0) {
		grid[x][y] = capturingPlacement(x, y) * player;
	}
	else {
		grid[x][y] = player;
	}
	//grid[x][y] = player * capturingPlacement(x, y); TODO:: FUTURE TASK POTENTIAL

	emptyCells.erase(remove(emptyCells.begin(), emptyCells.end(), (x * col + y)), emptyCells.end()); // Remove empty cell now it's used

	player = -1 * player;

	return true;
}

void Board::printBoard() {
	cout << "    ";
	for (int j = 0; j < col; j++) {
		cout << j + 1 << "   ";
	}
	cout << endl;

	for (int i = 0; i < row; i++) {
		cout << "  ";
		for (int j = 0; j < col; j++) {
			cout << " ---";
		}
		cout << endl;

		cout << (i + 1) << " |";

		for (int j = 0; j < col; j++) {
			if (grid[i][j] == 0) {
				cout << "   |";
			} else if (grid[i][j] > 0) {
				cout << " " << grid[i][j] << " |";
			} else if (grid[i][j] < 0) {
				cout << "" << grid[i][j] << " |";
			}
		}
		cout << endl;
	}
	cout << "  ";

	for (int j = 0; j < col; j++) {
		cout << " ---";
	}
	cout << endl << endl;
}

int Board::getCol() {
	return col;
}

int Board::getRow() {
	return row;
}

#endif /* BOARD_H_ */
