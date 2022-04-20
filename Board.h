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
	vector<Cell> cells;
	//vector<Cell> cellNeighbors;
	priority_queue<Cell> cellNeighbors;

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
				cells.push_back(Cell(i, j, grid[i][j]));
				emptyCells.push_back(i * col + j); // init indicies of empty cells (k = x * n + y)
			}
		}

		player = 1; // white has the first turn
	}

	~Board() {
		for (int i = 0; i < row; i++)
			delete[] grid[i];

		delete[] grid;
		
		cells.clear();
		
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

		for (int i = 0; i < cboard.cells.size(); i++) {
			cells.push_back(cboard.cells[i]);
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

	void setNeighbors(Cell target);
	
	int sumCells(priority_queue<Cell> Cells);

	//int sumNeigbours(const vector<Cell>& target);

	int getCol();

	int getRow();

};

// CURRENTLY ONLY DOES PIP COUNT TODO:: EXTEND CODE TO CAPTURE!!!
int Board::capturingPlacement(int x, int y) {

	Cell placement(x, y, 0);

	setNeighbors(placement);

	//get neighbour cells of x,y and store in some data structure
	
	if (cellNeighbors.size() < 2) {
		while (!cellNeighbors.empty()) {
			cellNeighbors.pop();
		}
		return 1;
	}
	else if (cellNeighbors.size() == 2) {
		/*
		*	if (abs(pipsum)) <= 6
		*		place with pipsum and remove neighbour moves
		*	else
		*		nothing to capture, add a 1 with the players sign
		*/

		if (sumCells(cellNeighbors) <= 6) {

			placement.heuristic = sumCells(cellNeighbors);
			
			while (!cellNeighbors.empty()) {
				grid[cellNeighbors.top().x][cellNeighbors.top().y] = 0; // set neigbor to 0
				emptyCells.push_back(cellNeighbors.top().x * col + cellNeighbors.top().y); // add back to emptyCells
				cellNeighbors.pop();
			}

			return placement.heuristic;
		}
		else {
			while (!cellNeighbors.empty()) {
				cellNeighbors.pop();
			}
			return 1;
		}

	}
	else if (cellNeighbors.size() > 2) {
		/*
		*	if (abs(pipsum)) <= 6
		*		place with pipsum and remove neighbour moves
		*	else if (pipsum of any combo of 2 neigh's > 6)
		*		nothing to capture, add a 1 with the players sign
		*	else
		*		capture combo that results in the highest pipsum placement
		*/

		if (sumCells(cellNeighbors) <= 6) {

			placement.heuristic = sumCells(cellNeighbors);

			while (!cellNeighbors.empty()) {
				grid[cellNeighbors.top().x][cellNeighbors.top().y] = 0; // set neigbor to 0
				emptyCells.push_back(cellNeighbors.top().x * col + cellNeighbors.top().y); // add back to emptyCells
				cellNeighbors.pop();
			}

			return placement.heuristic;
		}
		else
		{ 
			while (!cellNeighbors.empty()) {
				if (cellNeighbors.top().heuristic < 6) {
					Cell temp = cellNeighbors.top();
					cellNeighbors.pop();
					while (!cellNeighbors.empty()) {
						if (temp.heuristic + cellNeighbors.top().heuristic <= 6) {
							placement.heuristic += (temp.heuristic + cellNeighbors.top().heuristic);

							grid[cellNeighbors.top().x][cellNeighbors.top().y] = 0; // set neigbor to 0
							emptyCells.push_back(cellNeighbors.top().x * col + cellNeighbors.top().y); // add back to emptyCells

							grid[temp.x][temp.y] = 0; // set temp to 0
							emptyCells.push_back(temp.x * col + temp.y); // add back to emptyCells
							cellNeighbors.pop();
						}
						else {
							temp = cellNeighbors.top();
							cellNeighbors.pop();
						}
						
						
					}

				}
				else {
					cellNeighbors.pop();
				}
			}
			
			if (placement.heuristic == 0) {
				return 1;
			}
			return placement.heuristic;
			
		}

	}
}



void Board::setNeighbors(Cell target) {
	
	const int OFFSETX[] = { 0, 1, 0, -1 };
	const int OFFSETY[] = { -1, 0, 1, 0 };
	
	for (int i = 0; i < 4; i++) {
		int nx = target.x + OFFSETX[i];
		int ny = target.y + OFFSETY[i];
		if (! (nx < 0 || ny < 0 || nx >= row || ny >= col)) {
			if(abs(grid[nx][ny]) != 0){
				cellNeighbors.push(Cell(nx, ny, abs(grid[nx][ny])));
			}
			
		}
	}
}

int Board::sumCells(priority_queue<Cell> Cells) {
	int sum = 0;
	
	while (!Cells.empty()) {
		sum += Cells.top().heuristic;
		Cells.pop();
	}

	return sum;
}

//int Board::sumNeigbours(vector<Cell>& neighbours) {
//
//}



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

	
	grid[x][y] = capturingPlacement(x, y) * player;

	emptyCells.erase(remove(emptyCells.begin(), emptyCells.end(), (x * col + y)), emptyCells.end()); // Remove empty cell now it's used

	//TODO:: ineficeint when n is large
	for (auto& n : cells) {
		if (n.x == x && n.y == y) {
			n.heuristic = abs(grid[x][y]);
		}
	}

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
