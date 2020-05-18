#include "Board.h"
#pragma once

typedef struct {
	int score;
	std::string name;
} tSudoku;

typedef struct {
	tSudoku sudoku;
	tBoard board;
	bool fullBoard;
} tGame;

void initGame(tGame &game, const tSudoku &sudoku);
void displayGame(const tGame &game);
void loadGame(tGame &game, const tSudoku &sudoku);
int playSudoku();
void playGame(tGame &game, const tSudoku &sudoku);

void askValue(int &row, int &col);