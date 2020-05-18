#include "Game.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

float modeA(istream &file, int &ini, int end) {
	ifstream archivo;
	float score;
	cout << "Cards stolen this turn " << endl;
	for (int i = ini; i < end; i++) {
		archivo >> score;
		cout << score << endl;
		score += calculateScore(score);
	}
	cout << "THE SCORE IS:  " << score << endl;
	ini = end;
	return score;
}

float modeBHuman(ifstream &file, int &ini, int end) {
	float score;
	bool stolen = true;
	while (ini < end && stolen) {
		file >> score;
		score += calculateScore(score);
		if (score < PERFECT) {
			cout << "Want to keep drawining cards?" << endl;
			stolen = stealChoice();
		}
		else {
			stolen = false;
		}
	}
	ini = end;
	return score;
}

float modeBMachine(ifstream &file, int numCards, float humanScore) {
	float score, dif, dist;
	int i = 0;

	dif = humanScore - score;
	dist = PERFECT - score;

	cout << "Machine stole this during the turn" << endl;
	while (i < numCards && dif < dist) {
		file >> score;
		cout << score;
		score += calculateScore(score);
		i++;
	}
	return score;
}

void humanModeC(ifstream &file, tRemainingCards cards, float &score) {
	int cardfromfile;
	bool stolen = true;
	inicializeRemainingMODEC(cards);
	while (stolen) {
		file >> cardfromfile;
		if (cardfromfile > 9) {
			cards[0]--;
		}
		else {
			cards[cardfromfile]--;
		}
		cout << "Your new card is: " << cardfromfile << endl;
		score += calculateScore(cardfromfile);
		cout << "Your score is:  " << score << endl;
		if (score < PERFECT) {
			cout << "Want to keep drawining cards?" << endl;
			stolen = stealChoice();
		}
	}
}

void computerModeC(ifstream &file, tRemainingCards cards, float humanScore, float &score) {
	int cardfromfile;
	bool stolen = true;
	while (stolen) {
		file >> cardfromfile;
		if (cardfromfile > 9) {
			cards[0]--;
		}
		else {
			cards[cardfromfile]--;
		}
		cout << "Computer new card is: " << cardfromfile << endl;
		score += calculateScore(cardfromfile);
		cout << "Computer score this turn: " << score << endl;
		if (score == humanScore && canExceed(score, cards)) {
			stolen = false;
		}
	}
}

void humanModeD(tCardSet &deck, tRemainingCards cards, tCardSet &humanCards, float &score) {
	int cardsteal;
	bool stolen = true;
	int i = 0;
	inicialize(deck);
	inicializeRemainingMODED(deck, cards);

	while (stolen) {
		stealCard(deck, cardsteal);
		if (cardsteal > 9) {
			cards[0]--;
		}
		else {
			cards[cardsteal]--;
		}
		humanCards.card[i] = cardsteal;
		cout << "Your card(s): ";
		for (int j = 0; j < i; j++) {
			cout << humanCards.card[j] << " " << endl;
		}
		score += calculateScore(humanCards.card[i]);
		cout << "Score: " << score << endl;
		if (score < PERFECT) {
			cout << "Wanna draw a card?" << endl;
			stolen = stealChoice();
		}
		else {
			stolen = false;
		}

		addCard(deck, cardsteal);
		i++;
	}
}

void machineModeD(tCardSet &deck, tRemainingCards cards, float humanScore, tCardSet &computerScore, float &score) {
	int cardtosteal;
	bool steal = true;
	int i = 0;
	while (steal) {
		stealCard(deck, cardtosteal);
		if (cardtosteal > 9) {
			cards[0]--;
		}
		else {
			cards[cardtosteal]--;
		}
		addCard(deck, cardtosteal);
		computerScore.card[i] = cardtosteal;
		cout << "Machine card(s): ";
		for (int j = 0; j < i; j++) {
			cout << computerScore.card[j] << " " << endl;
		}
		score += calculateScore(cardtosteal);
		cout << "Machine score this turn:  " << score << endl;
		if (score < PERFECT) {
			steal = canExceed(score, cards);
		}
		else {
			steal = false;
		}

		i++;
	}
}

int setWinner(float humanScore, float computerScore) {
	int result;
	if (humanScore > computerScore || humanScore < PERFECT) {
		result = 1;
	}
	else if (humanScore < computerScore || humanScore < PERFECT) {
		result = 2;
	}
	else if (humanScore == computerScore) {
		result = rand() % 2;
	}
	return result;
}

bool stealChoice() {
	char decision;
	bool choice = false;
	cin >> decision;
	if (decision == 'Y' || decision == 'y') {
		choice = true;
	}
	return choice;
}

bool havewinner() {
	bool winner = false;

}