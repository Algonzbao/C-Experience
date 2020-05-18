#include "Game.h"
#include "checkML.h"
#include <iostream>
#include <string>

using namespace std;

void initGame(tGame &game, const tSudoku &sudoku) {
	init(game.board);
	game.fullBoard = false;
	game.sudoku = sudoku;
}
void displayGame(const tGame &game) {
	draw(game.board);
}
void loadGame(tGame &game, const tSudoku &sudoku) {
	load(sudoku.name, game.board);
}
int playSudoku() {
	int ch;
	cout << "1. Possible values for a cell" << endl;
	cout << "2. Put a value in a cell" << endl;
	cout << "3. Delete cells value" << endl;
	cout << "4. Restart the board" << endl;
	cout << "5. Autofill simple cells" << endl;
	cout << "0. Go back to main menu" << endl;
	cin >> ch;

	while (ch < 0 || ch > 5) {
		cout << "1. Possible values for a cell" << endl;
		cout << "2. Put a value in a cell" << endl;
		cout << "3. Delete cells value" << endl;
		cout << "4. Restart the board" << endl;
		cout << "5. Autofill simple cells" << endl;
		cout << "0. Go back to main menu" << endl;
		cin >> ch;
	}
	return ch;
}
void playGame(tGame &game, const tSudoku &sudoku) {
	int row, col, valueInt, op;
	bool samevalue = false;
	tBoard tablero;

	op = playSudoku();
	while (op != 0) {
		switch (op) {
		case 1:
			askValue(row, col);
			possible(game.board, row-1, col-1);
			break;
		case 2:
			askValue(row, col);
			possible(game.board, row-1, col-1);
			cout << "What value do you want to introduce in that row??" << endl;
			cin >> valueInt;
			place(game.board, row-1, col-1, valueInt,false);
			
			break;
		case 3:
			askValue(row, col);
			eraseCellVal(game.board, row-1, col-1);
			break;
		case 4:
			initGame(game, game.sudoku);
			loadGame(game, game.sudoku);;
			break;
		case 5:
			fillSimple(game.board);
			break;
		}
		displayGame(game);
		op = playSudoku();
	}
}
void askValue(int &row, int &col) {
	cout << "What cell info you want to know? introduce Row (1-9)" << endl;
	cin >> row;
	cout << "Introduce Column" << endl;
	cin >> col;
	while ((row < 1) || (row > 10) || (col < 1) || (col > 10)) {
		cout << "Some of the values were wrong, check they are between 1 and 9" << endl;
		cin >> row;
		cout << "Introduce Column" << endl;
		cin >> col;
	}
}
