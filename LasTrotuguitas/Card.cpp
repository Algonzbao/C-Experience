#include "Card.h"
#include "checkML.h"

using namespace std;




void createEmpty(tDeck &pack) { //Creates new card deck
	pack.cardNUM = 0;     // igualas a 0 el deck, pq quieres que esté vacío
}
bool take(tDeck &pack, tCard &card) { // robar carta
	bool taken = false;
	card = *pack.list[0];
	if (pack.cardNUM > 0) {
		for (int i = 1; i < pack.cardNUM; i++) {  // empieza en 1 pq 0 aqui no deberia contener nada
			*pack.list[i - 1] = *pack.list[i];  // es i-1 pq si pones i+1 cuando llega a MAX se sale
		}
		pack.cardNUM--;
		taken = true;
	}

	return taken;
}
void insert(tDeck &pack, tCard card) {// al usar la carta se mete al final del mazo

	if (pack.cardNUM < MAX_CARD_DECK) {
		*pack.list[pack.cardNUM] = card;
		pack.cardNUM++;
	}

}
void createRandomPack(tDeck &pack) { // create random deck 
	for (int i = 0; i < MAX_CARD_DECK; i++) {
		pack.list[i] = new tCard;
	}
	for (int i = 0; i < MAX_CARD_ADV; i++) {
		*pack.list[i] = (ADVANCE);
	}
	for (int i = MAX_CARD_ADV; i < MAX_CARD_LAS + MAX_CARD_ADV; i++) {
		*pack.list[i] = (LASER);
	}
	for (int i = MAX_CARD_ADV + MAX_CARD_LAS; i < MAX_CARD_LAS + MAX_CARD_ADV + MAX_CARD_LEFT; i++) {
		*pack.list[i] = (TURNLEFT);
	}
	for (int i = MAX_CARD_ADV + MAX_CARD_LAS + MAX_CARD_LEFT; i < MAX_CARD_DECK; i++) {
		*pack.list[i] = (TURNRIGHT);
	}

	pack.cardNUM = MAX_CARD_DECK;

	random_shuffle(&pack.list[0], &pack.list[MAX_CARD_DECK - 1]); //random desde el 1ero al último, se pasa por referencia pq es un struct
}
void free(tDeck &pack) {
	for (int i = 0; i < MAX_CARD_DECK; i++) {
		delete pack.list[i];
	}
}

