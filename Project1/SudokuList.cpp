#include "SudokuList.h"
#include "checkML.h"
#include <iostream>
#include <string>
#include <iomanip>


using namespace std;


void createList(tSudokuList &list) {
	list.counter = 0;
}
bool load(tSudokuList &list) {
	ifstream file;
	bool isopen = false;
	file.open(FILENAME);
	if (file.is_open()) {
		while (!file.eof()) {               
			file >> list.sudoku[list.counter].name;
			file >> list.sudoku[list.counter].score;
			list.counter++;
		}
		isopen = true;
	}
	else {
		cout << "Couldnt load sudokulist" << endl;
	}
	return isopen;

}
void display(const tSudokuList &list) {
	for (int i = 0; i < list.counter; i++) {
		cout << list.sudoku[i].name << endl;
	}
}
bool save(const tSudokuList &list) {
	ofstream file;
	bool saveOp = false;				
	int i = 0;
	file.open("FILENAME");
	if (file.is_open()) {
		while (i < list.counter) {
			file << list.sudoku[i].name;
			file << list.sudoku[i].score;
			i++;
		}
		saveOp = true;
	}
	return saveOp;
}
bool registerSudoku(tSudokuList &list) {
	bool registered = false;
	tSudoku newSudoku;
	string newFileName;
	int i = 0, newScore, newPosition;
	cout << "Can you introduce the name of the new sudoku?";
	cin >> newSudoku.name;
	cout << "Now please introduce the score ";
	cin >> newSudoku.score;
	if (list.counter < MAX_SUDOKUS) {
		if (!findFile(list, newSudoku.name)) {
			list.sudoku[list.counter-1].score = newSudoku.score;
			list.sudoku[list.counter-1].name = newSudoku.name;
			list.counter++;
			registered = true;
		}
	}
	cout << "Mensaje: El enunciado no especifica si hay que meter un nuevo tablero, lo que hice fué añadirlo a la lista" << endl;
	return registered;
}
bool findFile(const tSudokuList &list, const string &filename) {
	bool exist = false;
	int i = 0;
	while (i < list.counter && !exist) {
		if (filename == list.sudoku[i].name) {
			exist = true;
		}
		i++;
	}
	return exist;
}
int findPosition(const tSudokuList &list, const tSudoku &sudoku) {
	bool found = false;
	int pos = -1;
	int ini = 0, end = list.counter - 1, i;
	while (!found && (ini <= end)) {
		i = (ini + end) / 2;
		if (sudoku.score > list.sudoku[i].score) {
			ini = i + 1;
		}
		else if (sudoku.score < list.sudoku[i].score) {
			end = i - 1;
		}
		else if (list.sudoku[i].score == sudoku.score) {
			pos = i;
			found = true;
		}
	}
	return pos;
}
void sudokuDecision(tSudokuList &list, tGame &game) {
	string sudokuchoice;
	bool found = false;
	cout << "What sudoku file you want to play?" << endl;
	cin >> sudokuchoice;
	int i = 0;
	while (i < list.counter && !found) {
		if (sudokuchoice == list.sudoku[i].name) {
			game.sudoku = list.sudoku[i];
			found = true;
		}
		i++;
	}
	if (i == list.counter) {
		cout << "The sudoku either doesnt exists or the name is wrong " << endl;
	}
}