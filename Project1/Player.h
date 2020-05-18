#include "SudokuList.h"
#pragma once

const std::string FILEANAMEPLAYER = "playerlist.txt";

typedef struct {
	int score;
	std::string name;
}tPlayer;

typedef tPlayer* tPlayerPtr;

std::string toString(const tPlayer &player);
void modifyPlayer(tPlayer & player, int score);
bool operator<(const tPlayer &opLeft, const tPlayer &opRight);
bool smaller(const tPlayer &p1, const tPlayer &p2);
