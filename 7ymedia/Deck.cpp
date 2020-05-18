#include "Deck.h"

using namespace std;

int inicialize(tCardSet &deck) {
	ifstream deckchosen;
	int random;
	deck.cardNUM = 0;
	createDeck(deck, deckchosen, random);
}
void stealCard(tCardSet &deck, int &card) {
	card = deck.card[0];
	for (int i = 0; i < deck.cardNUM; i++) {
		deck.card[i] = deck.card[i + 1];
	}
	deck.cardNUM--;
}
void addCard(tCardSet &deck, int &card) {
	deck.card[deck.cardNUM] = card;
}
void createDeck(tCardSet &deck, ifstream &deckchosen, int random) {

	for (int i = 0; i < MAX_CARD; i++) {
		deckchosen >> deck.card[i];
	}
	random_shuffle(deck.card[0], deck.card[deck.cardNUM], random);
}

void inicializeRemainingMODEC(tRemainingCards values) {

	for (int i = 0; i < CARD_TYPE; i++) {
		if (i = 0) {
			values[i] = 12;
		}
		else {
			values[i] = 4;
		}
	}
}
// ESTA FUNCION ORDENA LAS REMAINING CARDS SEGÚN SU VALOR, ASÍ PUEDO CONTROLAR CUÁNTAS DE CADA TIPO QUEDAN
void inicializeRemainingMODED(const tCardSet cards, tRemainingCards values) {

	for (int i = 0; i < cards.cardNUM; i++) {
		if (0 < cards.card[i] && cards.card[i] < 8) {

			values[cards.card[i]]++;
		}
		else {
			values[0]++;
		}
	}
}
double calculateProb(float machineScore, const tRemainingCards cards) {
	int NumCards, allCards;
	double ifFail;
	ifFail = 7.5 - machineScore;

	for (int i = 0; i < CARD_TYPE; i++) {
		allCards += cards[i];
	}

	for (int i = floor(ifFail); i < CARD_TYPE; i++) {
		NumCards += cards[i];
	}
	return NumCards / allCards;
}

bool canExceed(float machineScore, const tRemainingCards cards) {
	bool risky = false;
	if (calculateProb(machineScore, cards) > 0.5) {
		risky = true;
	}
	return risky;
}