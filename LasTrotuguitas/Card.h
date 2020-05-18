#include <iostream>
#include <algorithm>


const int MAX_CARD_DECK = 38;
const int MAX_CARD_ADV = 18;
const int MAX_CARD_LEFT = 8;
const int MAX_CARD_RIGHT = 8;
const int MAX_CARD_LAS = 4;
const int CARD_TYPES = 4;
const int MAX_CARDS_HAND = 3;

typedef enum { ADVANCE, TURNLEFT, TURNRIGHT, LASER } tCard;

typedef tCard *tListPtr[MAX_CARD_DECK]; // Array de cartas.

typedef struct {
	tListPtr list;
	int cardNUM;
} tDeck;           //Estructura con lista y número de cartas en el mazo.

void createEmpty(tDeck &pack); //Creates new card deck
bool take(tDeck &pack, tCard &card); // robar carta
void insert(tDeck &pack, tCard card);  // al usar la carta se mete al final del maz
void createRandomPack(tDeck &pack); // create random deck 
void free(tDeck &pack);

