#include "Set.h"
#include <Windows.h>
#pragma once

const int CONST_BLACK = 0;
const int BLUE = 1;
const int RED = 4;

enum tState { EMPTY, FIXD, FILLED };

typedef struct {
	tState state;
	char number;
	tSet posVal;
}tCell;

void initCell(tCell &cell);
void fillCell(tCell &cell, char c, bool fixed = false);
void drawCell(const tCell &cell);
bool isSimple(const tCell & cell, int & number);
void bgColor(int color);
void defaultColour(int color = 0);