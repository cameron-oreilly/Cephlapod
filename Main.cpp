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
#include "ComputerPlayer.h"

int main() {
	srand(time(0));
	cout << "Example solution for high distinction level" << endl;

	Player *players[2];

	//players[0] = new HumanPlayer(1);
	players[0] = new RandomPlayer(1);
	players[1] = new ComputerPlayer(-1);

	cout << "Input size of the board (say (2,2), (2,3), (3,3), (3,5), (5,5) ... " << endl;

	int row, col;
	cin >> row >> col;

	Board board(row, col);
	CephalopodGame game(board, players);
	game.play();

	//below code can be used to run any number of games and capture the win results for each player
	// enable the code below and disable the single game above, set the players you want to simulate and run :)
	
	//int player1wins = 0;
	//int player2wins = 0;

	/*for (int i = 0; i < 100; i++) {
		Board board(row, col);
		CephalopodGame game(board, players);
		int result = game.play();
		if (result == 1) {
			player1wins++;
		}
		else if(result == -1) {
			player2wins++;
		}
	}

	cout << "random wins: " << player1wins << endl;
	cout << "computer wins: " << player2wins << endl;*/

	delete players[0];
	delete players[1];

	return 0;
}
