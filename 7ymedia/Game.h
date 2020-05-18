#ifndef Game_h
#define Game_h
#include "Deck.h"
#include "Score.h"
#include <iostream>
#include <fstream>
#include <string>

const float PERFECT = 7.5;

float modeA(istream &file, int &ini, int end);
float modeBHuman(ifstream &file, int &ini, int end);
float modeBMachine(ifstream &file, int numCards, float humanScore);
void humanModeC(ifstream &file, tRemainingCards cards, float &score);
void computerModeC(ifstream &file, tRemainingCards cards, float humanScore, float &score);
void humanModeD(tCardSet &deck, tRemainingCards cards, tCardSet &humanCards, float &score);
void machineModeD(tCardSet &deck, tRemainingCards cards, float humanScore, tCardSet &computerScore, float &score);
bool stealChoice();
int setWinner(float humanScore, float computerScore);

#endif