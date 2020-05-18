#ifndef Deck_h
#define Deck_h

#include <fstream>
#include <iostream>
#include <algorithm>

const int MAX_CARD = 40;

//HAY 8 TIPOS DE CARTAS, LAS DE 0.5 Y LAS DE 1-7. 
//EN LA POSICON 0 ESTÁN LAS 12 CARTAS QUE VALEN 0.5 
//Y EN EL RESTO LA DE LOS VALORES

const int CARD_TYPE = 8;


typedef int tList[MAX_CARD];

typedef int tRemainingCards[CARD_TYPE];

typedef struct {
	int cardNUM;
	tList card;
} tCardSet;

int inicialize(tCardSet &deck);
void stealCard(tCardSet &deck, int &card);
void addCard(tCardSet &deck, int &card);
void createDeck(tCardSet &deck, ifstream &deckchosen, int random);
void inicializeRemainingMODED(const tCardSet cards, tRemainingCards values);
void inicializeRemainingMODEC(tRemainingCards values);
double calculateProb(float machineScore, const tRemainingCards cards);
bool canExceed(float machineScore, const tRemainingCards cards);

#endif