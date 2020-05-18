#include "Board.h"
#include "checkML.h"
#include <string>
#include <fstream>
#include <iostream>

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
		string readline;
		succesful = true;
		for (int i = 0; i < ROW; i++) {
			getline(file, readline);
			for (int j = 0; j < COLUMN; j++) {
				fillCell(board[i][j], readline.at(j), true);
				if (board[i][j].state == FIXD) {
					setPosVal(board, i, j);
				}
			}
		}
		cleanPosVal(board);
	}
	return succesful;
}
void draw(const tBoard board) {
	int countregion = 0;
	int counterrow = 0;
	
	cout << "|| ----------------------------------- ||" << endl;
	for (int i = 0; i < ROW; i++) {
		bgColor(CONST_BLACK);
		cout << "||";
		for (int j = 0; j < COLUMN; j++) {
			drawCell(board[i][j]);
			cout << " " << board[i][j].number << " ";
			bgColor(CONST_BLACK);
			if (countregion == 2) {
				cout << "|";
				countregion = -1;
			}
			cout << "|";
			countregion++;
		}
		cout << endl;
		if (counterrow == 2 && i != 8) {
			cout << "|| ----------------------------------- ||" << endl;
			counterrow = -1;
		}
		cout << "|| ----------------------------------- ||" << endl;
		counterrow++;
	}

	defaultColour();
}
bool place(tBoard board, int row, int col, int valueint,bool isFive) {
	bool placed = false;
	int c = valueint + ASCIIVALUE;
	if (board[row][col].state == EMPTY && isIn(board[row][col].posVal, c)) {
		if (c != 32) {
			board[row][col].number = c;
			board[row][col].state = FILLED;
			placed = true;
			cleanPosVal(board);
		}
		else {
			board[row][col].number = ' ';
			board[row][col].state = EMPTY;
			placed = true;
		}
	}
	
	else if (board[row][col].state != EMPTY && !isFive) {
		cout << "Cell is alredy FILLED or FIXED" << endl;
	}
	else if(board[row][col].state == FILLED && !isFive) {
		cout << "The number is not part of the set of possible values" << endl;
	}
	return placed;
}
void eraseCellVal(tBoard board, int row, int col) {

	int value;
	if (board[row][col].state == FILLED) {
		value = board[row][col].number;
		for (int j = 0; j < COLUMN; j++) {
			add(board[row][j].posVal, value);
		}
		for (int j = 0; j < ROW; j++) {
			add(board[j][col].posVal, value);
		}
		addRegVal(board, theRegion(board[row][col], row, col), value);

		board[row][col].number = ' ';
		board[row][col].state = EMPTY;
	}
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
	cout << "This are the possible values for the current cell: ";
	while (i < tablero[row][col].posVal.counter) {
		cout << "| "<< tablero[row][col].posVal.listNum[i] << " | ";
		i++;
	}
	cout << " " << endl;
}

void fillSimple(tBoard board) {
	for (int i = 0; i < ROW; i++) {
		for (int j = 0; j < COLUMN; j++) {
			if (board[i][j].posVal.counter == 1) {
				place(board, i, j, board[i][j].posVal.listNum[0],true);
			}
		}
	}
}

void cleanPosVal(tBoard board) {
	int reg = 0;
	for (int i = 0; i < COLUMN; i++) {
		for (int j = 0; j < ROW; j++) {
			if (board[i][j].number != 32) {

				int deletenum = board[i][j].number;

				for (int row = 0; row < ROW; row++) {
					erase(board[i][row].posVal, deletenum);
				}
				for (int col = 0; col < COLUMN; col++) {
					erase(board[col][j].posVal, deletenum);
				}
				reg = theRegion(board[i][j], i, j);
				eraseRegVal(board, reg, deletenum);
			}
		}
	}
}
int theRegion(tCell &cell, int row, int column) {
	int region;
	if (row < 3) {
		if (column < 3) {
			region = 1;
		}
		else if (column > 2 && column < 6) {
			region = 2;
		}
		else {
			region = 3;
		}
	}
	else if (row > 2 && row < 6) {
		if (column < 3) {
			region = 4;
		}
		else if (column > 2 && column < 6) {
			region = 5;
		}
		else {
			region = 6;
		}
	}
	else{
		if (column < 3) {
			region = 7;
		}
		else if (column > 2 && column < 6) {
			region = 8;
		}
		else {
			region = 9;
		}
	}
	return region;
}
void eraseRegVal(tBoard board, int reg, int deletenum){
	//center region coords
	int x, y; 
	switch (reg) {
	case 1:
		x = 1; 
		y = 1; 
		break;
	case 2:
		x = 1;
		y = 4;
		break;
	case 3:
		x = 1;
		y = 7;
		break;
	case 4:
		x = 4;
		y = 1;
		break;
	case 5:
		x = 4;
		y = 4;
		break;
	case 6:
		x = 4;
		y = 7;
		break;
	case 7:
		x = 7;
		y = 1;
		break;
	case 8:
		x = 7;
		y = 4;
		break;
	case 9:
		x = 7;
		y = 7;
		break;
	}
	//travel nearby cells to centre cell of region 
	for (int i = y - 1; i < y + 2; i++) {
		erase(board[x-1][i].posVal, deletenum);
	}
	for (int i = y - 1; i < y + 2; i++) {
		erase(board[x][i].posVal, deletenum);
	}
	for (int i = y - 1; i < y + 2; i++) {
		erase(board[x + 1][i].posVal, deletenum);
	}
}
void addRegVal(tBoard board, int reg, int addnum) {
	//center region coords
	int x, y;
	switch (reg) {
	case 1:
		x = 1;
		y = 1;
		break;
	case 2:
		x = 1;
		y = 4;
		break;
	case 3:
		x = 1;
		y = 7;
		break;
	case 4:
		x = 4;
		y = 1;
		break;
	case 5:
		x = 4;
		y = 4;
		break;
	case 6:
		x = 4;
		y = 7;
		break;
	case 7:
		x = 7;
		y = 1;
		break;
	case 8:
		x = 7;
		y = 4;
		break;
	case 9:
		x = 7;
		y = 7;
		break;
	}
	//travel nearby cells to centre cell of region 
	for (int i = y - 1; i < y + 2; i++) {
		add(board[x - 1][i].posVal, addnum);
	}
	for (int i = y - 1; i < y + 2; i++) {
		add(board[x][i].posVal, addnum);
	}
	for (int i = y - 1; i < y + 2; i++) {
		add(board[x + 1][i].posVal, addnum);
	}
}
void setPosVal(tBoard board, int i, int j) {
	for (int x = 0; x < ROW; x++) {
		board[i][j].posVal.listNum[x] = 0;
	}
	board[i][j].posVal.counter = 1;
	board[i][j].posVal.listNum[board[i][j].posVal.counter - 1] = board[i][j].number - 48;
}