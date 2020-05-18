#include <iostream>
#include <fstream>
#pragma once

const int SET_SIZE = 9;
const int ASCIIVALUE = 48;

typedef struct {
	int counter;
	int listNum[SET_SIZE];
}tSet;

void emptySet(tSet &set);
void fullSet(tSet &set);
bool isIn(const tSet &set, int n);
void add(tSet &set, int n);
void erase(tSet &set, int n);
int size(const tSet &set);
bool one(const tSet &set, int &n);
void display(const tSet &set);
int searchPosition(const tSet &set, int n);
