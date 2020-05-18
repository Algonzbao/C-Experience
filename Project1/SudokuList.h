#include "Game.h"
#pragma once

int const MAX_SUDOKUS = 20;
const std::string FILENAME = "sudokulist.txt";

typedef struct {
	tSudoku sudoku[MAX_SUDOKUS];
	int counter;
}tSudokuList;

void createList(tSudokuList &list);
bool load(tSudokuList &list);
void display(const tSudokuList &list);
bool save(const tSudokuList &list);
bool registerSudoku(tSudokuList &list);
bool findFile(const tSudokuList &list, const std::string &filename);
int findPosition(const tSudokuList &list, const tSudoku &sudoku);
void sudokuDecision(tSudokuList &list, tGame &game);