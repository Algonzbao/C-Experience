#include "Board.h"
#include <string.h>
#include <fstream>

using namespace std;

void init(tBoard board) {
	for (int i = 0; i < ROW; i++) {
		for (int j = 0; j < COLUMN; j++) {
			initCell(board[i][j]);
		}
	}
}
bool load(const string &filename, tBoard board) {
	bool succesful = false;
	ifstream file;
	file.open(filename);
	if (!file.is_open()) {
		cout << "Error while opening the file" << endl;
	}
	else {
		char readchar;
		succesful = true;
		for (int i = 0; i < ROW; i++) {
			for (int j = 0; j < COLUMN; j++) {
				file >> readchar;
				fillCell(board[i][j], readchar, true);
			}
		}
	}
	return succesful;
}
void draw(const tBoard board) {
	for (int i = 0; i < ROW; i++) {
		for (int j = 0; j < COLUMN; j++) {
			drawCell(board[i][j]);
			cout << board[i][j].number; 
		}
		cout << endl;
	}

	defaultColour();
}
bool place(tBoard board, int row, int col, int c) {
	bool placed = false;
	if (board[row][col].state == EMPTY && isIn(board[row][col].posVal,c)) {
		board[row][col].number = c;
		board[row][col].state = FILLED;
		placed = true;

		for (int j = 0; j < COLUMN; j++) {
				erase(board[row][j].posVal, c);
			}
		for (int j = 0; j < ROW; j++) {
				erase(board[j][col].posVal, c);
			}
		// REGION PENDING RIOT APROVAL
	}
	else if (board[row][col].state != EMPTY) {
		cout << "Cell is alredy FILLED or FIXED" << endl;
	}
	else {
		cout << "The number is not part of the set of possible values" << endl;
	}
	return placed;
}
bool eraseCellVal(tBoard board, int row, int col) {
	bool erased = false;
	int value; 
	if (board[row][col].state == FILLED) {
	value = board[row][col].number;
	for (int j = 0; j < COLUMN; j++) {
		add(board[row][j].posVal, value);
	}
	for (int j = 0; j < ROW; j++) {
		add(board[j][col].posVal, value);
	}
	//REGION 
		board[row][col].number = ' ';
		board[row][col].state = EMPTY;
		erased = true;
	}
	return erased;
}
bool full(const tBoard board) {
	bool full = true;
	int i = 0, j = 0;
	while (i < ROW && !full) {
		while (j < COLUMN && !full) {
			if (board[i][j].state == EMPTY) {
				full = false;
			}
			j++;
		}
		i++;
	}
	return full;
}
void possible(const tBoard tablero, int row, int col) {
	int i = 0;
	while ( i < tablero[row][col].posVal.counter) {
		cout << tablero[row][col].posVal.listNum[i] << " " ;
		i++;
	}
}

void fillSimple(tBoard board) {
	for (int i = 0; i < ROW; i++){
		for (int j = 0; j < COLUMN; j++) {
			if (board[i][j].posVal.counter == 1) {
				place(board, i, j, board[i][j].posVal.listNum[0]);
			}
		}
	}
}
void restartBoard(tBoard board) {
	for (int i = 0; i < ROW; i++) {
		for (int j = 0; j < COLUMN; j++) {
			eraseCellVal(board, i, j);
		}
	}
}