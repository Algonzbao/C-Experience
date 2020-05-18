#include "SudokuList.h"
#include "Board.h"
#include "Cell.h"
#include "Player.h"
#include "PlayerList.h"
#include "Set.h"
#include "Game.h"
#include "checkML.h"

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int menu();



int main() {
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	tSudoku sudoku;
	tListPlayers playerList;
	tGame game;
	tSudokuList sudokuList;

	create(playerList);
	createList(sudokuList);

 	if (load(sudokuList) && load(playerList)) {
	
		int op;
		op = menu();
		while (op != 0) {
			switch (op) {
			case 1:
				display(sudokuList);
				sudokuDecision(sudokuList, game);
				initGame(game, game.sudoku);
				loadGame(game, game.sudoku);
				displayGame(game);
				playGame(game, sudoku);
				playerScore(playerList, sudokuList.sudoku[findPosition(sudokuList, game.sudoku)].score);
				rankSort(playerList);
				save(playerList);
				break;
			case 2:
				rankID(playerList);
				display(playerList);
				rankSort(playerList);
				break;
			case 3:
				display(playerList);
				break;
			case 4:
				if (!registerSudoku(sudokuList)) {
					cout << "The sudoku alredy exist in the File" << endl;
				}
				break;
			}
		
			op = menu();
			
		}
		cout << "THANKS FOR PLAYING THE FUCKING SUDOKU GAME QUE ME QUITa LAS GANAS DE VIVIR" << endl;
	}
}

int menu() {
	int op;
	cout << "\n1. PLAY" << endl;
	cout << "2. See players, sorted by ID" << endl;
	cout << "3. See players, sorted by score" << endl;
	cout << "4. Add sudoku" << endl;
	cout << "0. EXIT" << endl;
	cin >> op;

	while (op < 0 || op > 4) {
		cout << "1. PLAY" << endl;
		cout << "2. See players, sorted by ID" << endl;
		cout << "3. See players, sorted by score" << endl;
		cout << "4. Add sudoku" << endl;
		cout << "0. EXIT" << endl;
		cin >> op;
	}
	return op;
}

