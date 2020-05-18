#include <cstdlib>
#include <ctime>

using namespace std;

#include "Deck.h"
#include "Game.h"
#include "Score.h"



int menu();

int main() {
	srand(time(NULL));

	ifstream file;
	string archivo;
	int random, ini = 0, winner, newrandom;
	bool steal = true;
	tRemainingCards remaining;
	tCardSet deck, humanhand, computerhand;

	float humanscore, machinescore;
	random = 3 + rand() % (5 - 3 + 1);
	int op = menu();

	switch (op) {
	case 1:
		cout << "You are going to steal " << random << " cards" << endl;
		cout << "What file do you want to load for the deck ?" << endl;
		cin >> archivo;

		file.open(archivo);
		if (!file.is_open()) {
			cout << "Error opening the file" << endl;
		}
		else {
			while (steal) {
				humanscore = modeA(file, ini, random);
				newrandom = random + random;
				machinescore = modeA(file, random, newrandom);
				cout << "WANT TO PLAY ANOTHER TURN??";
				steal = stealChoice();
			}
			winner = setWinner(humanscore, machinescore);
			if (winner == 1) {
				cout << "YOU WIN, THAT WAS EASY" << endl;
				//añadir victoria en el contador
			}
			else {
				cout << "MACHINE WON, LUCKY DAY" << endl;
				//añadir victoria 
			}
		}
		break;

	case 2:
		cout << "You are going to steal " << random << " cards" << endl;
		cout << "What file do you want to load for the deck ?" << endl;
		cin >> archivo;

		file.open(archivo);
		if (!file.is_open()) {
			cout << "Error opening the file" << endl;
		}
		else {
			while (steal) {
				humanscore = modeBHuman(file, ini, random);
				newrandom = random + random;
				machinescore = modeBMachine(file, random, newrandom);
				if (humanscore < 7.5) {
					cout << "WANT TO PLAY ANOTHER TURN??";
					steal = stealChoice();
				}
			}
			winner = setWinner(humanscore, machinescore);
			if (winner == 1) {
				cout << "YOU WIN, THAT WAS EASY" << endl;
				//añadir victoria en el contador
			}
			else {
				cout << "MACHINE WON, LUCKY DAY" << endl;
				//añadir victoria 
			}
		}
		break;

	case 3:

		cout << "What file do you want to load for the deck ?" << endl;
		cin >> archivo;

		file.open(archivo);
		if (!file.is_open()) {
			cout << "Error opening the file" << endl;
		}
		else {
			while (steal) {
				humanModeC(file, remaining, humanscore);
				computerModeC(file, remaining, humanscore, machinescore);
				cout << "WANT TO KEEP STEALING ";
				steal = stealChoice();
			}
			winner = setWinner(humanscore, machinescore);
			if (winner == 1) {
				cout << "YOU WIN, THAT WAS EASY" << endl;
				//añadir victoria en el contador
			}
			else {
				cout << "MACHINE WON, LUCKY DAY" << endl;
				//añadir victoria 
			}
		}

		break;

	case 4:
		while (steal) {
			humanModeD(deck, remaining, humanhand, humanscore);
			machineModeD(deck, remaining, humanscore, computerhand, machinescore);
			cout << "WANT TO KEEP STEALING ";
			steal = stealChoice();
		}
		winner = setWinner(humanscore, machinescore);
		if (winner == 1) {
			cout << "YOU WIN, THAT WAS EASY" << endl;
			//añadir victoria en el contador
		}
		else {
			cout << "MACHINE WON, LUCKY DAY" << endl;
			//añadir victoria 
		}
		break;
	default:
		return 0;
		break;
	}
	op = menu();
}

int menu() {
	int option = -1;
	while ((option < 0) || (option > 4)) {
		cout << "1 - Play (Mode A)" << endl;
		cout << "2 - Play (Mode B)" << endl;
		cout << "3 - Play (Mode C)" << endl;
		cout << "4 - Play (Mode D)" << endl;
		cout << "0 - Exit" << endl;
		cout << "Option: ";
		cin >> option;
		if ((option < 0) || (option > 4)) {
			cout << "Option not valid try another one..." << endl;
		}
	}
	return option;
}