#include "Cell.h"

using namespace std;

void initCell(tCell &cell) {
	cell.state = EMPTY;
	fullSet(cell.posVal);
}
void fillCell(tCell &cell, char c, bool fixedvalue) {
	if (c ==  ' ' ){
		cell.state = EMPTY;
	}
	else {
		cell.number = c;
		if (fixedvalue) {
			cell.state = FIXD;
		}
		else {
			cell.state = FILLED;
		}
	} 
}
void drawCell(const tCell &cell) {
	switch (cell.state) {

	case EMPTY:
		bgColor(BLACK);
		break;
	case FIXD:
		bgColor(BLUE);
		break;
	case FILLED:
		bgColor(RED);
		break;
	}
}
bool isSimple(const tCell & cell, int & number) {
	bool simple = false;
	if (cell.state == EMPTY && one(cell.posVal, number)) {
		simple = true;
	}
	return simple;
}
void bgColor(int color) {
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(handle, 15 | (color << 4));
}
void defaultColour(int color = 0) {
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(handle, 15 | (color << 4));
}