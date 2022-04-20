/*********** Declaration*******
I hereby certify that no part of this assignment has been copied from any
other student’s work or from any other source. No part of the code has
been written/produced for me by another person.
I hold a copy of this assignment that I can produce if the original is
lost or damaged.
**************************/

#include<iostream>
#include<time.h>
#include<algorithm>
#include<unordered_map>
#include<sstream>
#include<vector>
#include<set>
#include<queue>

using namespace std;

#include "Cell.h"
#include "Board.h"
#include "Player.h"
#include "CephalopodGame.h"
#include "HumanPlayer.h"
#include "RandomPlayer.h"
#include "MiniMaxPlayer.h"

int main() {
	srand(time(0));
	cout << "Example solution for high distinction level" << endl;

	Player *players[2];

	//players[0] = new HumanPlayer(1);
	players[0] = new RandomPlayer(1);
	players[1] = new MiniMaxPlayer(-1);

	cout << "Input size of the board (say (2,2), (2,3), (3,3), (3,5), (5,5) ... " << endl;

	int row, col;
	cin >> row >> col;

	Board board(row, col);
	CephalopodGame game(board, players);
	game.play();

	delete players[0];
	delete players[1];

	return 0;
}
