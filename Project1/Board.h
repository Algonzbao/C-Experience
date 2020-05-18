#include "Cell.h"
#pragma once

const int ROW = 9;
const int COLUMN = 9;
const int FULLBOARD = 81;

typedef tCell tBoard[ROW][COLUMN];

void init(tBoard board);
bool load(const std::string &filename, tBoard board);
void draw(const tBoard board);
bool place(tBoard board, int row, int col, int c, bool isFive);
void eraseCellVal(tBoard board, int row, int col);
bool full(const tBoard board);
void possible(const tBoard tablero, int row, int col);
void fillSimple(tBoard board);

void cleanPosVal(tBoard board);
int theRegion(tCell &cell, int row, int column);
void eraseRegVal(tBoard board, int reg, int deletenum);
void addRegVal(tBoard board, int reg, int addnum);
void setPosVal(tBoard board, int i, int j);