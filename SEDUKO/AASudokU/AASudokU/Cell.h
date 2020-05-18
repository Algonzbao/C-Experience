#include "Set.h"
#include <Windows.h>
 
const int BLACK = 0;
const int BLUE = 1;
const int RED = 4;

typedef enum {EMPTY , FIXD, FILLED}  tState;

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